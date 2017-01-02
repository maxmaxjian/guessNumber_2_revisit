#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <utility>
#include <vector>
#include <numeric>

namespace std {
    std::ostream & operator<<(std::ostream &os, const std::pair<int,std::vector<int>> & pr) {
	os << "pick " << pr.first << ": ";
	std::copy(pr.second.begin(), pr.second.end(), std::ostream_iterator<int>(os, " "));
	os << "= " << std::accumulate(pr.second.begin(), pr.second.end(), 0);
	return os;
    }
}

class solution {
public:
    int getMoneyAmount(int n) {
	std::map<int,std::vector<int>> dict;
	for (int i = 1; i < n; i++)
	{
	    auto temp = getPaths(n, i, std::vector<int>());
	    // std::cout << "pick " << i << "\n";
	    // std::for_each(temp.begin(), temp.end(),
	    // 		  [](const std::vector<int> & vec){
	    // 		      std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	    // 		      std::cout << std::endl;
	    // 		  });
	    dict[i] = *std::max_element(temp.begin(), temp.end(),
					[](const std::vector<int> & v1, const std::vector<int> & v2){
					    return std::accumulate(v1.begin(), v1.end(), 0) < std::accumulate(v2.begin(), v2.end(), 0);
					});
	}
	std::copy(dict.begin(), dict.end(), std::ostream_iterator<std::pair<int,std::vector<int>>>(std::cout, "\n"));
	auto it = std::max_element(dict.begin(), dict.end(),
				   [](const std::pair<int,std::vector<int>> & p1, const std::pair<int,std::vector<int>> & p2){
				       return std::accumulate(p1.second.begin(), p1.second.end(),0) < std::accumulate(p2.second.begin(), p2.second.end(),0);
				   });

	return std::accumulate(it->second.begin(), it->second.end(),0);
    }

private:
    std::vector<std::vector<int>> getPaths(int n, int pick, const std::vector<int> & curr) {
	std::vector<std::vector<int>> result;
	std::vector<int> next = getNext(n, pick, curr);
	if (next.empty())
	    result.push_back(curr);
	else {
	    for (auto nx : next) {
		auto cpy = curr;
		cpy.push_back(nx);
		auto temp = getPaths(n, pick, cpy);
		std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
	    }
	}
	return result;
    }
    
    std::vector<int> getNext(int n, int pick, const std::vector<int> & curr) {
	std::vector<int> next;
	if (curr.empty()) {
	    for (int i = n-1; i > 0; i--)
		if (i != pick) {
		    next.push_back(i);
		}
	}
	else {
	    if (curr.back() < pick) {
		for (int i = curr.back()+1; i< n; i++)
		    if (i != pick && std::find(curr.begin(), curr.end(),i) == curr.end())
			next.push_back(i);
	    }
	    else {
		for (int i = 1; i < curr.back(); i++)
		    if (i != pick && std::find(curr.begin(), curr.end(),i) == curr.end())
			next.push_back(i);
	    }
	}
	return next;
    }
};

int main() {
    int num = 10;

    solution soln;
    auto money = soln.getMoneyAmount(num);
    std::cout << "The amount of money needed is:\n"
	      << money << std::endl;
}
