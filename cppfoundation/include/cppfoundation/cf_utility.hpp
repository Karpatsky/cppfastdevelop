/*
 * Copyright 2013, Jeffery Qiu. All rights reserved.
 *
 * Licensed under the GNU LESSER GENERAL PUBLIC LICENSE(the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.gnu.org/licenses/lgpl.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//// Author: Jeffery Qiu (dungeonsnd at gmail dot com)
////

#ifndef _HEADER_FILE_CFD_CF_UTILITY_HPP_
#define _HEADER_FILE_CFD_CF_UTILITY_HPP_

#include "cppfoundation/cf_root.hpp"
#include "cppfoundation/cf_exception.hpp"

namespace cf
{

#ifndef CF_ERR
#define CF_ERR(msg) \
    { \
        fprintf(stderr,"Error! %s,file=%s,line=%d,errno=%d,strerror=%s \n",msg,__FILE__,__LINE__,errno,strerror(errno)); \
        exit(1); \
    }
#endif // ERR


inline cf_void Gettimeofday(cf_uint64 & seconds, cf_uint32 & useconds)
{
    static struct timeval tv;
    cf_int rt =gettimeofday(&tv, NULL);
    if (-1==rt)
        _THROW(cf::SyscallExecuteError, "Failed to execute gettimeofday !");
    seconds =(cf_uint64)tv.tv_sec;
    useconds =(cf_uint32)tv.tv_usec;
}

inline cf_char * GenRandString(cf_char * str,const cf_uint32 len)
{
    srand(time(NULL));
    cf_uint32 i;
    for(i=0; i<len; ++i)
        str[i]='a'+rand()%26;
    return str;
}

inline std::string String2Hex(cf_cpstr input,cf_uint32 inputLength)
{
    if(inputLength<1)
        return "";
    std::string output;
    std::string everyone(3,'\0');
    for(cf_uint32 i =0; i<inputLength; i++)
    {
        memset(&everyone[0],0,everyone.size());
        snprintf(&everyone[0],everyone.size(),"%02x",input[i]);
        output.append (everyone.c_str(),everyone.size()-1);
    }
    return output;
}

inline std::string String2HexD(cf_cpstr input,cf_uint32 inputLength)
{
    if(inputLength<1)
        return "";
    std::string output;
    std::string everyone(5,'\0');
    for(cf_uint32 i =0; i<inputLength; i++)
    {
        memset(&everyone[0],0,everyone.size());
        snprintf(&everyone[0],everyone.size(),"\\x%02x",input[i]);
        output.append (everyone.c_str(),everyone.size()-1);
    }
    return output;
}

#ifdef _DEBUG
#define CF_SWITCH_PRINT 0
#endif

#ifndef CF_PRINT_FUNC
#if CF_SWITCH_PRINT
#define CF_PRINT_FUNC \
    { \
        cf_uint64 seconds =0; \
        cf_uint32 useconds =0; \
        cf::Gettimeofday(seconds, useconds); \
        fprintf(stdout,"%llu %03u %03u [%d %s:%d,%s] \n", \
                seconds,useconds/1000,useconds%1000,int(getpid()),\
                strrchr (__FILE__, '/') == 0 ? __FILE__ : strrchr (__FILE__, '/') + 1,\
                __LINE__,__FUNCTION__); \
    }

#define CF_PRINT_FUNC_ARGS(MSG) \
    { \
        cf_uint64 seconds =0; \
        cf_uint32 useconds =0; \
        cf::Gettimeofday(seconds, useconds); \
        fprintf(stdout,"%llu %03u %03u [%s:%d,%s] %s\n", \
                seconds,useconds/1000,useconds%1000,\
                strrchr (__FILE__, '/') == 0 ? __FILE__ : strrchr (__FILE__, '/') + 1,\
                __LINE__,__FUNCTION__ , MSG); \
    }
#else
#define CF_PRINT_FUNC ;
#endif //  CF_SWITCH_PRINT    
#endif // CF_PRINT_FUNC

cf_void SetProcessDaemon();

cf_void IgnoreSignals();


cf_void GenerateRandString(cf_uint32 stringLength, std::string & output);

// type traits
// If invoker give "T * obj", use these PointerTraits can get the 'T' type.
/**
e.g.

template < typename T >
void func()
{
    typedef typename PointerTraits<T>::ValueType TypeOfT;
    // TypeOfT is 'int'
}

int * x =new int
func(x);
**/
template <typename D>
struct PointerTraits
{
    typedef D TraitsValueType;
    typedef D * TraitsPointerType;
};
template <typename D>
struct PointerTraits<D *>
{
    typedef D  TraitsValueType;
    typedef D * TraitsPointerType;
};


} // namespace cf

#endif // _HEADER_FILE_CFD_CF_UTILITY_HPP_

