//
// Created by Benjamin Schulz on 22/07/16.
//

#ifndef GAMESPARKSTESTS_RT_TEST_UTILS_HPP
#define GAMESPARKSTESTS_RT_TEST_UTILS_HPP

#include <vector>
#include <string>
#include "../base/TestPlatform.h"

class TestUtils
{
    public:
        struct TestSession
        {
            TestSession() {}
            TestSession(const std::string& token, const std::string& host, const std::string& port, const std::string& name)
            :token(token), host(host), port(port), name(name) {}

            std::string token;
            std::string host;
            std::string port;
            std::string name;
        };

		static std::vector<TestSession> getSessions()
		{
			auto rt_session_0 = TestPlatform::get_rt_seesion_0();
			auto rt_session_1 = TestPlatform::get_rt_seesion_1();

			auto a0 = splitString(rt_session_0);
			auto a1 = splitString(rt_session_1);

			checkOrExit(a0.size() == 4, "the RT_SESSION_0 environment variable must be pipe delimited 'server|port|playerId|token' like generated by tokengenerator.py");
			checkOrExit(a1.size() == 4, "the RT_SESSION_1 environment variable must be pipe delimited 'server|port|playerId|token' like generated by tokengenerator.py");

			return{
				TestSession(a0[3], a0[0] + ".gamesparks.net", a0[1], a0[2]),
				TestSession(a1[3], a1[0] + ".gamesparks.net", a1[1], a1[2])
			};
		}

	private:
		static std::vector<std::string> splitString(const std::string& s)
		{
			std::vector<std::string> elems;
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, '|')) {
				elems.push_back(item);
			}
			return elems;
		}

		static void checkOrExit(bool exp, const std::string& msg)
		{
			if (!exp)
			{
				std::cerr << msg << std::endl;
				exit(2);
			}
		}
};


#endif //GAMESPARKSTESTS_RT_TEST_UTILS_HPP