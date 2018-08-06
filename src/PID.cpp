#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double kp, double ki, double kd) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;

    total_error = 0.0;
    total_times = 0;

    next_adjust = 0;
    twiddle_step = 0;
    params_adjustment = {0.1 * Kp, 0.1 * Ki, 0.1 * Kd};
    best_error = std::numeric_limits<double>::max();

}

void PID::UpdateError(double cte) {
    i_error += cte;
    d_error = p_error == 0.0 ? 0.0 : cte - p_error;
    p_error = cte;


    total_times++;
//    if ((total_times % STEPS_FOR_TWIDDLE) >  (STEPS_FOR_TWIDDLE * 0.5)) {
    total_error += cte * cte;
//    }


    UpdatePidParams();

    if (total_times % STEPS_FOR_TWIDDLE == 0) {
        std::cout << "best error:" << best_error << ",total times:" << total_times << ",Kp:" << Kp << ",Ki:" << Ki
                  << ",Kd:" << Kd << ",next_adjust:" << next_adjust << ",twiddle_step:" << twiddle_step << std::endl;
    }
}

void PID::UpdatePidParams() {
    if (!USE_TWIDDLE) {
        return;
    }

    if (total_times <= STEPS_FOR_TWIDDLE || total_times % STEPS_FOR_TWIDDLE != 0) {
        return;
    }


    next_adjust = next_adjust % params_adjustment.size();

    switch (twiddle_step) {
        case 0:
            AddParam(next_adjust, params_adjustment[next_adjust]);
            if (total_error < best_error) {
                best_error = total_error;
            }
            total_error = 0.0;
            twiddle_step = 1;
            break;
        case 1:
            if (total_error < best_error) {
                params_adjustment[next_adjust] = params_adjustment[next_adjust] * 1.1;
                best_error = total_error;


                next_adjust = (next_adjust + 1) % params_adjustment.size();
                AddParam(next_adjust, params_adjustment[next_adjust]);
                twiddle_step = 1;
                total_error = 0.0;
                return;
            }

            AddParam(next_adjust, (-2) * params_adjustment[next_adjust]);
            twiddle_step = 2;
            total_error = 0.0;
            break;
        case 2:
            if (total_error < best_error) {
                best_error = total_error;
                params_adjustment[next_adjust] = params_adjustment[next_adjust] * 1.1;

                next_adjust = (next_adjust + 1) % params_adjustment.size();
                AddParam(next_adjust, params_adjustment[next_adjust]);
                twiddle_step = 1;
                total_error = 0.0;
                return;
            }

            AddParam(next_adjust, params_adjustment[next_adjust]);
            params_adjustment[next_adjust] = 0.9 * params_adjustment[next_adjust];


            next_adjust = (next_adjust + 1) % params_adjustment.size();
            AddParam(next_adjust, params_adjustment[next_adjust]);
            twiddle_step = 1;
            total_error = 0.0;


    }
}

void PID::AddParam(int index, double addition) {
    switch (index) {
        case 0:
            Kp += addition;
            break;
        case 1:
            Ki += addition;
            break;
        case 2:
            Kd += addition;
            break;
    }
}

double PID::TotalError() {
    return total_error;
}

