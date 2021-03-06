#include <iostream>
#include "xtechnical_indicators.hpp"

using namespace std;

int main() {
    cout << "Hello world!" << endl;
    xtechnical_indicators::MW<double> iMW(30);
    xtechnical_indicators::MMA<double> iMMA(5);
    xtechnical_indicators::SMA<double> iSMA(5);
    xtechnical_indicators::AMA<double> iAMA(10);
    xtechnical_indicators::NoLagMa<double> iNoLagMa(10);
    xtechnical_indicators::RoC<double> iRoC(3);
    xtechnical_indicators::VWMA<double> iVWMA(20);


    for(int i = 1; i <= 50; ++i) {
        //int temp = -(i*2);//i % 4;
        int temp = i % 4;
        iMW.update(temp);

        double std_dev_value = 0;
        int err_std_dev = iMW.get_std_dev(std_dev_value, 10, 0);
        if(err_std_dev == 0) {
            double mean_value = 0;
            iMW.get_average(mean_value, 4, 0);
            double angle_value = 0;
            iMW.compare_data(
                angle_value,
                xtechnical_common::CALCULATE_ANGLE,
                true,
                mean_value - 2*std_dev_value,
                mean_value + 2*std_dev_value,
                10,
                0);
            std::cout << "ANGLE " << angle_value << std::endl;
        }

        double mma_out = 0.0;
        iMMA.update(temp, mma_out);

        double ama_out = 0.0;
        iAMA.update(temp, ama_out);

        double sma_out = 0.0;
        iSMA.update(temp, sma_out);

        double roc_out = 0.0;
        iRoC.update(temp, roc_out);

        double vwma_out = 0.0;
        iVWMA.update(temp,i, vwma_out);

        std::vector<double> rsi;
        std::vector<double> sma;
        std::vector<double> std_dev;
        iMW.get_rsi_array(rsi, 3, 15, 3);
        iMW.get_average_and_std_dev_array(sma, std_dev, 10, 22, 3);

        std::cout << "step: " << i << " temp " << temp << " is init: " << iMW.is_init() << std::endl;
        for(size_t i = 0; i < sma.size(); ++i) {
            std::cout << "rsi: " << rsi[i] << " sma: " << sma[i] << " std_dev: " << std_dev[i] << std::endl;
        }
        std::cout << "MMA: " << mma_out << " SMA " << sma_out << " AMA " << ama_out << std::endl;
        std::cout << "RoC: " << roc_out << std::endl;
        std::cout << "VWMA: " << vwma_out << std::endl;
    }

    double rsi_value = 0;
    iMW.get_rsi(rsi_value, 15);
    std::cout << "rsi_value: " << rsi_value << std::endl;
    double aver_value = 0;
    iMW.get_average(aver_value, 22);
    std::cout << "aver_value: " << aver_value << std::endl;
    double std_dev_value = 0;
    iMW.get_std_dev(std_dev_value, 22);
    std::cout << "std_dev: " << std_dev_value << std::endl;

    xtechnical_indicators::VCMA<double> iVCMA;
    std::cout << iVCMA.update(2,1) << std::endl;
    std::cout << iVCMA.update(3,0.5) << std::endl;
    std::cout << iVCMA.update(1,0.5) << std::endl;
    return 0;
}
