#ifndef PID_H
#define PID_H

#include <vector>

class PID {
public:
    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;


    unsigned total_times;

    unsigned twiddle_step;
    std::vector<double> params_adjustment;
    double best_error;
    double total_error;
    unsigned next_adjust;

    static const bool USE_TWIDDLE = false;
    //about one circle
    static const int STEPS_FOR_TWIDDLE = 1800;

    /*
    * Coefficients
    */
    double Kp;
    double Ki;
    double Kd;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double kp, double ki, double kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    void UpdatePidParams();

    void AddParam(int index, double addition);

    /*
    * Calculate the total PID error.
    */
    double TotalError();

};

#endif /* PID_H */
