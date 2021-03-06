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

#ifndef _HEADER_FILE_CFD_CF_ROOT_HPP_
#define _HEADER_FILE_CFD_CF_ROOT_HPP_

#include "cppfoundation/cf_system_stub.h"
#include "cppfoundation/cf_include_cpp.hpp"

namespace cf
{

class Object
{
public:
    Object() {}
    virtual ~Object() {}

    std::string GetClassName()
    {
        return typeid(this).name();
    }
};

class NonCopyable : public Object
{
protected:
    NonCopyable() {}
    virtual ~NonCopyable() {}
private:
    NonCopyable( const NonCopyable & );
    const NonCopyable & operator=( const NonCopyable & );
};

} // namespace cf

#endif // _HEADER_FILE_CFD_CF_ROOT_HPP_
