#include "data_structure.hpp"

using namespace std;
using namespace itis;

int main(int argc, char **argv) {
  string pathToAdd;
  cout << "Enter the path to semester-work-red-black-tree\\dataset\\data\\add\\";
  cin >> pathToAdd;
  cout << "Enter the path to save results of testing 'Delete'";
  string strDel;
  cin >> strDel;
  cout << "Enter the path to save results of testing 'Insert'";
  string strIns;
  cin >> strIns;
  cout << "Enter the path to save results of testing 'Search'";
  string strSer;
  cin >> strSer;


  int intTab[] = {100, 500, 1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 750000, 1000000, 2500000, 5000000};
  string strDir[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
  string strTab[] = {"\\100.csv",    "\\500.csv",     "\\1000.csv",    "\\5000.csv",   "\\10000.csv",
                     "\\25000.csv",  "\\50000.csv",   "\\100000.csv",  "\\250000.csv", "\\500000.csv",
                     "\\750000.csv", "\\1000000.csv", "\\2500000.csv", "\\5000000.csv"};
  //DeleteTests
  ofstream output_streamDT(strDel);
  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j < 10; ++j) {
      string path = pathToAdd;
      path += strDir[j];
      path += strTab[i];
      ifstream input_stream(path, ios::ios_base::app);
      RBTree tree;
      for (int k = 0; k < intTab[i]; ++k) {
        int x;
        input_stream >> x;
        tree.insert(x);
      }
      for (int o = 0; o < 10; ++o) {
        const auto seed = chrono::system_clock::now().time_since_epoch().count();
        auto engine = mt19937(seed);
        auto dist = uniform_int_distribution(0, 5000);
        const auto time_point_before = chrono::steady_clock::now();
        tree.deleteByVal(dist(engine));
        const auto time_point_after = chrono::steady_clock::now();
        const auto time_diff = time_point_after - time_point_before;
        const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
        output_streamDT << time_elapsed_ns << '\n';
        tree.insert(dist(engine));
      }
    }
  }//endDeleteTests

  //insertTests
  ofstream output_streamIT(strIns);
  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j < 10; ++j) {
      string path = pathToAdd;
      path += strDir[j];
      path += strTab[i];
      ifstream input_stream(path, ios::ios_base::app);
      RBTree tree;
      for (int k = 0; k < intTab[i]; ++k) {
        int x;
        input_stream >> x;
        tree.insert(x);
      }
      for (int o = 0; o < 10; ++o) {
        const auto seed = chrono::system_clock::now().time_since_epoch().count();
        auto engine = mt19937(seed);
        auto dist = uniform_int_distribution(0, 5000);
        const auto time_point_before = chrono::steady_clock::now();
        tree.insert(dist(engine));
        const auto time_point_after = chrono::steady_clock::now();
        const auto time_diff = time_point_after - time_point_before;
        const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
        output_streamIT << time_elapsed_ns << '\n';
      }
    }
  }//endInsertTests

  //searchTests
  ofstream output_streamST(strSer);
  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j < 10; ++j) {
      string path = pathToAdd;
      path += strDir[j];
      path += strTab[i];
      ifstream input_stream(path, ios::ios_base::app);
      RBTree tree;
      for (int k = 0; k < intTab[i]; ++k) {
        int x;
        input_stream >> x;
        tree.insert(x);
      }
      for (int o = 0; o < 10; ++o) {
        const auto seed = chrono::system_clock::now().time_since_epoch().count();
        auto engine = mt19937(seed);
        auto dist = uniform_int_distribution(0, 5000);
        const auto time_point_before = chrono::steady_clock::now();
        tree.search(dist(engine));
        const auto time_point_after = chrono::steady_clock::now();
        const auto time_diff = time_point_after - time_point_before;
        const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
        output_streamST << time_elapsed_ns << '\n';
      }
    }
  }//endSearchTests
  return 0;
}