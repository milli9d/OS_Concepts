/**
 * @file fib_threads.cpp
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

#include <iostream>

#include "simple_fib.hpp"

namespace os_cpp
{

/**
 * @brief
 * @param n
 * @return
 */
long long unsigned int simple_fib::_fib_r(long long unsigned int n)
{
	/* exit if base condition */
	if (n <= 1u) {
		return n;
	}

	/* fetch if already in memo */
	if (_memo[n] != 0u) {
		return _memo[n];
	}

	/* calculate and memoize */
	long long unsigned int out = _fib_r(n - 1) + _fib_r(n - 2);
	_memo[n] = out;

	return out;
}

void simple_fib::_print_fib_r(long long unsigned int n)
{
	for (int i = 0; i < n; i++) {
		printf("FIB[%d] = %llu\n", i + 1u, _fib_r(i));
		usleep(500u);
	}
}

/**
 * @brief
 * @param n
 */
simple_fib::simple_fib(long long unsigned int n)
{
	_memo.reserve(n);
	_print_fib_r(n);
}

/* ========================================================================== */
/* Mutli-Threaded version */
/* ========================================================================== */

void *simple_fib_multi_thread::_thread_handler(void *args)
{
	/* copy argument data to stack */
	fib_thread_cfg_s access = **((fib_thread_cfg_s **)args);

	/* free heap memory */
	free(*((fib_thread_cfg_s **)args));
	*((fib_thread_cfg_s **)args) = NULL;

	/* allow next thread to be queued */
	sem_post(&access._this->_sem);

	printf("Thread Spawned %lld %lld\n", access.start, access.end);

	for (int i = access.start; i < access.end; i++) {
		long long unsigned int out = access._this->_fib_r(i);
		printf("Fib[%d] = %llu\n", i, out);
	}

	return NULL;
}

/**
 * @brief
 * @param n
 */
simple_fib_multi_thread::simple_fib_multi_thread(long long unsigned int n, uint16_t num_threads)
	: _num_threads(num_threads)
{
	/* sanity checks */
	if (num_threads == 0u) {
		printf("ERROR: invalid num of threads = %d\n", num_threads);
		return;
	}

	sem_init(&_sem, 0, 0u);

	/* add threads */
	_threads.reserve(num_threads);

	/* init memo */
	_memo.reserve(n);

	for (int i = 0u; i < 256u; i++) {
		long long unsigned int out = _fib_r(i);
	}

	_thread_range_sz = n / _num_threads;

	for (int i = 0; i < _num_threads; i++) {
		fib_thread_cfg_s *temp_cfg = (fib_thread_cfg_s *)malloc(sizeof(fib_thread_cfg_s));

		temp_cfg->start = i * _thread_range_sz;
		temp_cfg->end = (i + 1) * _thread_range_sz;
		temp_cfg->_this = this;

		pthread_t *temp = new pthread_t();

		pthread_create(temp, NULL, simple_fib_multi_thread::_thread_handler, &temp_cfg);
		_threads.push_back(temp);

		sem_wait(&_sem);
	}
}

simple_fib_multi_thread::~simple_fib_multi_thread()
{
	for (pthread_t *thread : _threads) {
		void **rc = NULL;
		pthread_join(*thread, rc);
	}
}

} // namespace os_cpp