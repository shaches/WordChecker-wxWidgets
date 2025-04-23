#include <iostream>
#include <stdlib.h>

#include "WordCheckerConfig.h"

#include "MathFunctions.h"

int main(int argc, char *argv[]){

	if(__cplusplus == 202302L){
		std::cout << "AHAHAHAHHA" << std::endl;
	}

	if(argc < 2){
		// report version
		std::cout << argv[0] << "Version " << WordChecker_VERSION_MAJOR << "."
				  << WordChecker_VERSION_MINOR << "." 
				  << WordChecker_VERSION_PATCH << "."
				  << WordChecker_VERSION_TWEAK
				  << std::endl; 
		std::cout << "Usage: " << argv[0] << " number" << std::endl;

		return 1;
	}

	double hehe = std::atof(argv[1]);
	double hehesqrt = mathfunctions::sqrt(hehe);

	std::cout << hehesqrt << std::endl;
	
	return 0;
}
