#include <SgLib.h>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "usage: " << argv[0]<<"[table file path]"<< endl;
		return 0;
	}

	namespace fs = boost::filesystem;
	fs::path fullpath(argv[1]);
	if (!fs::exists(fullpath))
	{
		SG_TRACE2(argv[1], "not exist!");
		return 1;
	}

	fs::recursive_directory_iterator end_iter;
	for (fs::recursive_directory_iterator iter(fullpath); iter != end_iter; iter++){
		try{
			if (fs::is_directory(*iter)){
				std::cout << *iter << "is dir" << std::endl;
				//ret.push_back(iter->path().string());
			}
			else{
				//ret.push_back(iter->path().string());
				std::cout << *iter << " is a file" << std::endl;
			}
		}
		catch (const std::exception & ex){
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}

	system("pause");

	return 0;
}