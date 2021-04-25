#include <fstream>      // ifstream, ofstream
#include <iostream>     // cout
#include <sstream>      // stringstream
#include <string>       // string, getline
#include <string_view>  // string_view
#include <random>       // mt19937_64, random_device
#include <chrono>       // system_clock

using namespace std;

// абсолютный путь до набора данных
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};

int main(int argc, char** argv) {
  int intTab[] = {100, 500, 1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 750000, 1000000, 2500000, 5000000};
  string strDir[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
  string strTab[] = {"\\100.csv",    "\\500.csv",     "\\1000.csv",    "\\5000.csv",   "\\10000.csv",
                     "\\25000.csv",  "\\50000.csv",   "\\100000.csv",  "\\250000.csv", "\\500000.csv",
                     "\\750000.csv", "\\1000000.csv", "\\2500000.csv", "\\5000000.csv"};
  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j < 10; ++j) {
      string path = "C:\\Users\\danil\\CLionProjects\\semester-work-red-black-tree\\dataset\\data\\add\\";
      path += strDir[j];
      path += strTab[i];
      ofstream output_stream(path, ios::ios_base::app);
      const auto seed = chrono::system_clock::now().time_since_epoch().count();
      auto engine = mt19937(seed);  // без seed`а генератор будет выдавать одни и те же значения
      auto dist = uniform_int_distribution(0, 5000);  // равновероятное распределение генерируемых чисел
      for (int counter = 0; counter < intTab[i]; counter++) {
        output_stream << dist(engine) << '\n';
      }
    }
  }
  return 0;
}