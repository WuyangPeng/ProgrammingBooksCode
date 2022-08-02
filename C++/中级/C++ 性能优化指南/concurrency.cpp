# include "test_driver.h"
# include <thread>
# include <future>
# include <atomic>
# include "stopwatch03.h"

typedef unsigned long long counter_t;

bool atomic_test_1() {
	struct foo {
		int i;
		int j;
		int k;
		int l;
	};
	std::atomic<foo> f;
	foo f1{ 2,3,4,5 };
	f.store(f1);
	foo f2 = f.load();
	return (f2.i == 2 && f2.j == 3 && f2.k == 4 && f2.l == 5 && f.is_lock_free() == false);
}

void f1(int n) {
	std::cout << "thread " << n << std::endl;
}

void thread_example() {
	std::thread t1;          // thread variable, not a thread
	t1 = std::thread(f1, 1); // assign a thread to a thread variable
	t1.join();               // wait for thread to complete

	std::thread t2(f1, 2);
	std::thread t3(std::move(t2)); // can't copy thread, move it instead
	std::thread t4([]() {return;});// works with lambdas too
	t4.detach();
	t3.join();
}

void promise_future_example_1() {
	auto meaning = [](std::promise<int>& prom) {
		prom.set_value(42);
	};

	std::promise<int> prom;
	std::thread(meaning, std::ref(prom)).detach();

	std::future<int> result = prom.get_future();
	std::cout << "the meaning of life: " << result.get() << "\n";
}

void promise_future_example_2() {
	auto meaning = std::packaged_task<int(int)>([](int n) { return n; });
	auto result  = meaning.get_future();
	auto t       = std::thread(std::move(meaning), 42);

	std::cout << "the meaning of life: " << result.get() << "\n";
	t.join();
}

void promise_future_example_3() {
	auto meaning = [](int n) { return n; };
	auto result = std::async(std::move(meaning), 42);
	std::cout << "the meaning of life: " << result.get() << "\n";
}

bool thread_startstop_test(unsigned long multiplier) {
	std::thread t;
	{
		Stopwatch s("thread start/stop");
		for (unsigned i = 0; i < 10 * multiplier; ++i) {
			t = std::thread([]() { return; });
			t.join();
		}
	}
	{
		Stopwatch s("thread start/stop 2");
		for (unsigned i = 0; i < 10 * multiplier; ++i)
			std::thread([]() { return; }).join();
	}
	{
		Stopwatch s("thread start/detatch");
		for (unsigned i = 0; i < 10 * multiplier; ++i)
			std::thread([]() { return; }).detach();
	}
	return true;
}

bool async_startstop_test(unsigned long multiplier) {
	{
		Stopwatch s("async task start/stop");
		for (unsigned i = 0; i < 10 * multiplier; ++i)
			std::async(std::launch::async, []() { return; });
	}
	{
		Stopwatch s("deferred async task start/stop");
		for (unsigned i = 0; i < 10 * multiplier; ++i)
			std::async(std::launch::deferred, []() { return; });
	}
	return true;
}

void timewaster(unsigned iterations) {
	unsigned fibonacci(unsigned);
	for (counter_t i = 0; i < iterations; ++i)
		fibonacci(30);
}

// something for the computer to do
// note: this function is actually de-optimized to make it slower
unsigned fibonacci(unsigned i) {
	if (i > 2)
		return fibonacci(i - 1) + fibonacci(i - 2);
	else
		return 1;
}

void multithreaded_timewaster(unsigned iterations, unsigned threads) {
	std::vector<std::thread> t;
	t.reserve(threads);
	for (unsigned i = 0; i < threads; ++i)
		t.push_back(std::thread(timewaster, iterations / threads));
	for (unsigned i = 0; i < threads; ++i)
		t[i].join();
}

bool multi_thread_test(unsigned long multiplier) {
	bool rc = true;
	{
		Stopwatch s("unthreaded test");
		timewaster(multiplier);
	}
	{
		Stopwatch s("1 thread");
		multithreaded_timewaster(multiplier, 1);
	}
	{
		Stopwatch s("2 threads");
		multithreaded_timewaster(multiplier, 2);
	}
	{
		Stopwatch s("3 threads");
		multithreaded_timewaster(multiplier, 3);
	}
	{
		Stopwatch s("4 threads");
		multithreaded_timewaster(multiplier, 4);
	}
	{
		Stopwatch s("5 threads");
		multithreaded_timewaster(multiplier, 5);
	}
	{
		Stopwatch s("10 threads");
		multithreaded_timewaster(multiplier, 10);
	}
	{
		Stopwatch s("100 threads");
		multithreaded_timewaster(multiplier, 100);
	}
	{
		Stopwatch s("1000 threads");
		multithreaded_timewaster(multiplier, 1000);
	}
	return true;
}

void cv_example() {
	std::mutex m;
	std::condition_variable cv;
	bool terminate = false;
	int shared_data = 0;
	int counter = 0;

	auto consumer = [&]() {
		std::unique_lock<std::mutex> lk(m);
		do {
			while (!(terminate || shared_data != 0))
				cv.wait(lk);
			if (terminate)
				break;
		//	std::cout << "consuming " << shared_data << std::endl;
			shared_data = 0;
			cv.notify_one();
		} while (true);
	};

	auto producer = [&]() {
		std::unique_lock<std::mutex> lk(m);
		for (counter = 1; true; ++counter) {
			cv.wait(lk, [&]() {return terminate || shared_data == 0;});
			if (terminate)
				break;
			shared_data = counter;
		//	std::cout << "producing " << shared_data << std::endl;
			cv.notify_one();
		}
	};

	auto p = std::thread(producer);
	auto c = std::thread(consumer);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	{
		std::lock_guard<std::mutex> l(m);
		terminate = true;
	}
	std::cout << "total items consumed " << counter << std::endl;
	cv.notify_all();
	p.join();
	c.join();
}

int test_atomic(int test_no, unsigned long multiplier) {
	bool rc = true;
	switch (test_no) {
	default: return -1;
	case 0:	 return  4;
	case 1: 
	//	std::cout << "number of hardware threads is "
	//			  << std::thread::hardware_concurrency()
	//			  << std::endl;
		{
			std::atomic<counter_t> x;
			rc &= x.is_lock_free();
			rc &= atomic_test_1();
		}
		{
			rc &= (fibonacci(1) == 1);
			rc &= (fibonacci(2) == 1);
			rc &= (fibonacci(3) == 2);
			rc &= (fibonacci(4) == 3);
			rc &= (fibonacci(5) == 5);
			rc &= (fibonacci(6) == 8);
			rc &= (fibonacci(7) == 13);
			rc &= (fibonacci(40) > 100000000);
		}
		{
		//	thread_example();
			cv_example();
			promise_future_example_1();
			promise_future_example_2();
			promise_future_example_3();
		}
		break;

	case 2:
		{
			volatile unsigned n = 30;
			{
				Stopwatch s("fibonacci test");
				for (counter_t i = 0, iterations = multiplier; i < iterations; ++i)
					rc &= (fibonacci(n) < (1u << n));
			}
		}
		break;

	case 3:
		{
			Stopwatch s("atomic test");
			std::atomic<counter_t> x;
			for (counter_t i = 0, iterations = 10'000'000 * multiplier; i < iterations; ++i)
				x = i;
			rc = x != 0;
		}
		{
			Stopwatch s("non-atomic test");
			counter_t x;
			for (counter_t i = 0, iterations = 10'000'000 * multiplier; i < iterations; ++i)
				x = i;
			rc = x != 0;
		}
		break;

	case 4:
		{
		//	rc &= thread_startstop_test(multiplier);
		//	rc &= async_startstop_test(multiplier);
		//	rc &= multi_thread_test(multiplier);
		}
		break;
	}
	return rc ? 1 : 0;
}

int main(int argc, char** argv) {
	test_driver(test_atomic, argc, argv);
	return 0;
}