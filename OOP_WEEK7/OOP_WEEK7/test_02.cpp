#include <iostream>
#include <vector>

int main() {
	std::vector<int> vec;
	vec.push_back(11);
	vec.push_back(22);
	vec.push_back(33);
	vec.push_back(44);
	// Remove an element from vector if its value is equal to 22
	for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
		if (*itr == 22) {
			vec.erase(itr); //벡터 값이 바뀔 때 벡터 내부의 메모리 변화에 따라 오류 발생
			//itr = vec.earse(itr); 또는
			//itr = vec.begin();으로 초기화 하여 오류 해결
		}
	}
	// Print Entire vector contents after the removal of element
	for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
		std::cout << "Vector element: " << *itr << std::endl;
	}
	getchar();
}