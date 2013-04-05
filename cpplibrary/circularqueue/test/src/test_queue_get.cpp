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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string>
#include <memory>
#include <time.h>

#include "cppfoundation/cf_ipc.hpp"
#include "circularqueue/cl_posixshm_circular_queue.hpp"
#include "circularqueue/cl_circular_queue.hpp"

#define _AUTO_

template < typename QUEUETYPE >
cf_void Run(QUEUETYPE * queue)
{
    
    time_t t;
    time_t tm =time(&t);
    srand((unsigned cf_int)tm);
    
	while(1)
	{
        printf("---------------------------------------------------\n");
	    std::string data;
	    queue->Get(data);
	    printf("%s \n",data.c_str());
	    fflush(stdout);

	    std::string close ="close";
	    cf_int rt =strncmp(close.c_str(), data.c_str(),close.size());
	    if(0==rt)
		break;
	}
}

cf_void demo0(size_t size)
{
	std::string name ="sample_queue";
	cf_int oflag = cf::ipcdefs::FLAG_RDWR;
	std::shared_ptr < cf::PosixShM > shm( new cf::PosixShM(name.c_str(),size,oflag) );
	std::shared_ptr < cl::cq::CircularQueue > queue( new cl::cq::CircularQueue(shm->Get()) );
    Run(queue.get());
}

cf_void demo1(size_t size)
{
	std::string name ="sample_queue";
    bool creator =false;
    cf_int oflag = cf::ipcdefs::FLAG_RDWR;
	std::shared_ptr < cl::cq::PosixShmCircularQueue > queue( new cl::cq::PosixShmCircularQueue(name,creator,size,oflag) );
    Run(queue.get());
}

cf_int main(cf_int argc,cf_char * argv[])
{
    size_t size =0;
    if(argc<2)
        size =999;
    else
        size =size_t(atol(argv[1]));
//    demo0(size);
    demo1(size);
    return 0;
}
