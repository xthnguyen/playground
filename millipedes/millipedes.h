#include <papi.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <chrono>
#include <type_traits>

namespace kindergarten {

namespace detail
{

	//https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
	static inline uint64_t rdtsc()
	{
		//1. not recommended for Windows platform
		//2. will be impacted by multi-cpu(s), interupts, pre-emptions 
		//3. can be re-ordered
		uint64_t rax, rdx;
		__asm__ __volatile__("rdtsc" : "=a"(rax), "=d"(rdx));
		return (rdx << 32) | rax;
	}

	static inline uint64_t rdtscp()
	{
		uint64_t rax, rcx, rdx;
		__asm__ __volatile__("rdtscp" : "=a"(rax), "=d"(rdx), "=c"(rcx));
		return (rdx << 32) | rax;
	}


	template<int... EventT>
	struct PapiCounter
	{
		bool start()
		{
			int result = ::PAPI_start_counters(const_cast<int*>(events_.data()), count_);
		       if (result != PAPI_OK)
		       {
			       //if this fails, likely we need
			       //sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
			       std::cout << "failed to register " << PAPI_strerror(result) << std::endl;
			       return false;
		       }	       

		       for (int i = 0; i < count_; i++)
		       {
			       char event_name[PAPI_MAX_STR_LEN];
			       PAPI_event_code_to_name(events_[i], event_name);
				event_names_[i] =  std::string(event_name);
		       }

		       return true;

		}

		void stop()
		{
			int result = ::PAPI_stop_counters(const_cast<long long*>(event_counters_.data()), count_);
			if (result != PAPI_OK)
			{
				std::cout << "failed to unregister " << PAPI_strerror(result) << std::endl;
			}

		}

		long get_counter(int index)
		{
			return event_counters_[index];
		}

		const std::string& get_counter_name(int index) const
		{
			return event_names_[index];
		}
	private:
		static constexpr int count_ = sizeof...(EventT);
		std::array<long long, count_> event_counters_;
		std::array<std::string, count_> event_names_;
	public:
		static std::array<int, count_> events_;//= {{EventT...}};//c++1z
	};


        using CacheCounter = PapiCounter<PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L3_TCM>; 
   template<>	std::array<int, 3> PapiCounter<PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L3_TCM>::events_ = {{PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L3_TCM}};

	struct TestCaseBase
	{
		virtual void run() const = 0;
	};

	template<typename TestLamdaT>
	struct TestCase final : TestCaseBase
	{
		TestCase(TestLamdaT test_lamda) : test_lamda_(test_lamda)
		{
			
		}

		void run() const final 
		{
			test_lamda_();
		}
	
	private:
		TestLamdaT test_lamda_;

	};

	struct TestSuite 
	{
	
		template <typename TestWrapperT>
		TestSuite& add(TestWrapperT test_wrapper)
		{
			tests_.emplace_back(new TestCase<TestWrapperT>(test_wrapper));
			return *this;
		}	

		void run(int iterations)
		{
			for(auto& t : tests_)
			{
				CacheCounter cache_counter;
				cache_counter.start();

				auto ts1 = rdtscp();
				for(int i = 0; i < iterations; ++i)
				{
					t->run();
				}
				auto ts2 = rdtscp();
				
				cache_counter.stop();

				auto elapsed = (float)(ts2 - ts1) / iterations;


				std::cout << "took " << (ts2 - ts1) << std::endl;

				for(int k = 0; k < 3; k++)
				{
					std::cout <<
						cache_counter.get_counter_name(k) <<
						"  " << 
						cache_counter.get_counter(k) <<
						std::endl;
				}
			}
		}
	
	private:
		std::vector<std::unique_ptr<TestCaseBase>> tests_;

	};

}



}



