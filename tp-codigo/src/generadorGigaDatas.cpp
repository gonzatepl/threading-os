#include <iostream>
#include <fstream>
#include <vector>



int main() {

	std::ofstream fout;
	fout.open("../data/GigaGigaData.txt"); // abre archivo
	
	std::vector<char> letra={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


	for (int i1= 0; i1< 25; i1++){
		for (int i2= 0; i2< 25; i2++){
			for (int i3= 0; i3< 25; i3++){
				for (int i4= 1; i4< 25; i4++){
					
						


									fout << letra[i1]<< letra[i2]<< letra[i3]<< letra[i4]<< std::endl;


				}
			}
		}
	}


	
	fout.close(); // cierra archivo
	return 0;
}
