#ifndef CMD_H
#define CMD_H

#include <map>
#include <string>

using namespace std;

class Cmd{
private:
	static map<string, string> parameters;

	static bool isParametr(const char* str){
		if (str[0] == '-')
			return true;

		return false;
	}

public:
	static void init(int argc, char* argv[]){
		parameters.clear();
		if (argc > 1){
			for(int i = 1; i < argc - 1; ++i){
				if (isParametr(argv[i])){
					if (!isParametr(argv[i + 1]))
						parameters[argv[i] + 1] = argv[i + 1];
					else
						parameters[argv[i] + 1] = "";
				}
			}

			if (isParametr(argv[argc - 1]))
				parameters[argv[argc - 1] + 1] = "";
		}
	}

	static bool isParameterExists(const string& key){
		return (parameters.find(key) != parameters.end());
	}

	static const string& getParameterValue(const string& key){
		return parameters[key];
	}

	static const string CMD_NAME;
	static const string CMD_CONFIG_FILE;
	static const string CMD_LAUNCH_DISPATCHER;
};

map<string, string> Cmd::parameters;
const string Cmd::CMD_NAME = "name";
const string Cmd::CMD_CONFIG_FILE = "config_file";
const string Cmd::CMD_LAUNCH_DISPATCHER = "launch_dispatcher";

#endif

