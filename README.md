# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program



----


## Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?

- P stands of proportional,means that the car will steer in proportion to the cross-track error, or CTE. It takes into account only the present value of CTE. As shown in the video below,the car may overshooting.

[P controller video](./P_controller.mov)

- I stands of integral,means that the car will conside the total CTE past time, which is used to reduce systematic bias.

- D for derivative is the change in CTE from one value to the next. With derivative (D) part, the controller output is proportional to the rate of change of cte (its derivative),which is used to reduce overshooting.After tuned all PID parameters,the car behaves as expected. It steers smoothly along the central line.

[PID controller video](./PID_controller.mov)




## Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

Initially, the controller was tuned manually,I adjust the size of the PID parameters to small, so that the car can run normally on the track.
```
pid.Init(0.22, 0.001, 1.1)
```

After that,I tuned the parameters with so-called twiddle.Adjust the value of PID in turn to minimize the total error.

```
best error:1.79769e+308,total times:1800,Kp:0.196262,Ki:0.000999,Kd:1.61051,next_adjust:0,twiddle_step:0
best error:856.07,total times:3600,Kp:0.215888,Ki:0.000999,Kd:1.61051,next_adjust:0,twiddle_step:1
best error:350.169,total times:5400,Kp:0.215888,Ki:0.0010989,Kd:1.61051,next_adjust:1,twiddle_step:1
best error:318.501,total times:9000,Kp:0.215888,Ki:0.0008991,Kd:1.77156,next_adjust:2,twiddle_step:1
best error:318.501,total times:41400,Kp:0.215888,Ki:0.0008991,Kd:1.72792,next_adjust:2,twiddle_step:1
best error:274.736,total times:43200,Kp:0.231626,Ki:0.0008991,Kd:1.72792,next_adjust:0,twiddle_step:1
```

The final parameters are
```
pid.Init(0.215888, 0.0008991, 1.72792);
```

