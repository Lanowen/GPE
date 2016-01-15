#pragma once

namespace gpe
{
	class EventData
	{
	public:
		EventData();
		virtual ~EventData();

		void* data_;
	};
}