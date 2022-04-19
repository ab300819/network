#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct MediaAsset {
	virtual ~MediaAsset() = default;  // make it polymorphic
};

struct Song : public MediaAsset {
	std::string artist;
	std::string title;
	Song(const std::string& artist_, const std::string& title_)
		: artist{artist_}, title{title_} {}
};

std::ostream& operator<<(std::ostream& strm, const Song& a) {
	return strm << "A(" << a.title << ")";
}

struct Photo : public MediaAsset {
	std::string date;
	std::string location;
	std::string subject;
	Photo(const std::string& date_, const std::string& location_,
		  const std::string& subject_)
		: date{date_}, location{location_}, subject{subject_} {}
};

int main() {
	auto p1 = std::make_shared<Song>("The Beatles",
									 "Im Happy Just to Dance With You");
	auto p2 = std::make_shared<Song>("Lady Gaga", "Just Dance");
	std::cout << p1->title << std::endl;
	std::cout << p2->title << std::endl;

	p1.swap(p2);
	std::cout << p1->title << std::endl;
	std::cout << p2->title << std::endl;
	return EXIT_SUCCESS;
}