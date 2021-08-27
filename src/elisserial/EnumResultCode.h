//
// Created by chiplua on 2021/8/27.
//

#ifndef ELISRS128WINTEST_ENUMRESULTCODE_H
#define ELISRS128WINTEST_ENUMRESULTCODE_H

namespace ElisSerial {
    enum class EnumResultCode {
        SUCCESS,        //命令执行成功
        FAIL,           //命令执行失败
        BUSY,           //命令执行失败
        PARSE_ERROR = 0x04//解包出错请求重发
    };
}
#endif //ELISRS128WINTEST_ENUMRESULTCODE_H
