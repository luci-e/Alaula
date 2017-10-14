#pragma once
#include <plog/Record.h>
#include <plog/Util.h>
#include <iomanip>

namespace plog
{
    class VLCformatter
    {
    public:
        static util::nstring header(){
            return PLOG_NSTR("ConnectionId;Transmitter;Receiver;Simtime;Type;Value1;Value2;Value3;Value4;Value5;Value6\n");
        }

        static util::nstring format(const Record& record){
            util::nstringstream ss;

            util::nstring message = record.getMessage();
            ss << message << PLOG_NSTR("\n");

            return ss.str();
        }
    };
}
