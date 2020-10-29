#include <iostream>
#include <algorithm>
#include <random>

#include "CDataset.hpp"
#include "LinAlg.hpp"

using namespace std;

void CDataset::Plot()
{
    plot.Title(plotName);

    plot.PlotVector(LinAlg::Transpose(X)[0], LinAlg::Transpose(X)[1], "y");

    cout << endl
         << "Press enter to continue..." << endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
}

void CDataset::ShuffleData()
{
    std::random_device rd;
    std::mt19937 eng1({rd()});
    auto eng2 = eng1;
    std::shuffle(std::begin(X), std::end(X), eng1);
    std::shuffle(std::begin(y), std::end(y), eng2);
}
