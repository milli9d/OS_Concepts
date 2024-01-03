/**
 * @file fib_threads.hpp
 *
 * @brief POSIX Threads testbench
 *
 * <long_description>
 */

/**
 * This file is part of OS_Concepts.
 *
 * OS_Concepts is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * OS_Concepts is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OS_Concepts. If not, see <https://www.gnu.org/licenses/>.
 */

#include <bits/stdc++.h>
#include <iostream>

#include <pthread.h>
#include <unistd.h>

namespace os_cpp
{

class os_shell {
private:
	pthread_t _thread_handle;

public:
	os_shell();
	~os_shell();
};

/* ========================================================================= */
/* Private API */
/* ========================================================================= */

/* ========================================================================= */
/* Public API */
/* ========================================================================= */

os_shell::os_shell()
{
}

}