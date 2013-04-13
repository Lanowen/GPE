#include <GPENet.hpp>

namespace GPENet {

	boost::asio::io_service SocketBase::io_service;

	void OrderedDatagamHistory::Update(UINT32 ack, UINT32 ack_bitfield){

		
		UINT32 diff_ack_bitfield = lastProcessedAck_bitfield;

		int offset = ack - lastProcessedAck;

		int bitfieldSize = sizeof(ack_bitfield) * 8;
		if(offset > 0){
			//push in previous ack
			ack_bitfield <<= 1;
			ack_bitfield |= 1;

			if(--offset > 1){
				//offset
				ack_bitfield <<= (offset - 1);
			}

			diff_ack_bitfield <<= (offset-1);

			lastProcessedAck = ack;
		}
		else if(offset <= bitfieldSize) {
			ack_bitfield |= 1<<(-offset - 2); //-1 for lastAck and -1 becuase 1 is already in first bit position
		}
		// else too bad

		diff_ack_bitfield ^= ack_bitfield;

		if(history.size() > 0){
			int x = history.size();

			//std::cout << "Begin history update " << ack << " " << diff_ack_bitfield << " " << history.size() << std::endl;
			//Util::dout <<  "Begin history update " << ack << " " << diff_ack_bitfield << " " << history.size() << std::endl;

			std::map<UINT32, HistoryEntry>::iterator itr = history.begin();
			std::map<UINT32, HistoryEntry>::iterator next;

			if(history.begin() == history.end())
				next = history.end();
			else
				next = history.begin()++;

			for(; itr != history.end();){
				if(itr->first > ack + 32){ //its gone beyond the ack, resend
					int dsf = itr->first;
					owner->SendDatagram(itr->second.datagram);
					history.erase(itr);
					//std::cout << "1: " << dsf << " got removed from the history! " << history.size() << std::endl;
					//Util::dout << "1: " << dsf << " got removed from the history! " << history.size() << std::endl;

					if(next == history.end())
						break;

					itr = next++;
					continue;
				}

				break;
			}

			//std::cout << "1: end for " << history.size() << std::endl;
			//Util::dout << "1: end for " << history.size() << std::endl;
				
			if(history.find(ack) != history.end()){
				history.erase(ack);
				//std::cout << "2: " << ack << " got removed from the history! " << history.size() << std::endl;
				//Util::dout << "2: " << ack << " got removed from the history! " << history.size() << std::endl;
			}

			
			for(int i = ack-1; diff_ack_bitfield > 0; diff_ack_bitfield >>= 1, i--){
				if((diff_ack_bitfield & 1) != 0){
					if(history.find(i) != history.end()){
						history.erase(i);
						//std::cout << "3: " << i << " got removed from the history! " << history.size() << std::endl;
						//Util::dout << "3: " << i << " got removed from the history! " << history.size() << std::endl;
					}
					
				}
			}
			//std::cout << "3: end for " << history.size() << std::endl;
			//Util::dout << "3: end for " << history.size() << std::endl;
		}
	}

}