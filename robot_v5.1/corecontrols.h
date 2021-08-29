#pragma once

#include "defines.h"

//const float R_ANG = map(MAXANG, 0, 180, 0, PI);

byte getMaxSpeed()
{
    static byte s = map(analogRead(POT), 0, 1023, MINSPEED, 255);
    return s;
}

byte MAXSPEED = getMaxSpeed;

byte getFrontDist()
{
    int dist = sonarfront.ping_cm();
    delay(2);
    if ((dist > 0) && (dist < 50)) {
        dist = 0;
        for (int i = 0; i < 5; i++) {
            dist += sonarfront.ping_cm();
            delay(1);
        }
        dist = dist / 5;
    }
    return dist;
}

byte getSideDist()
{
    int dist = sonarside.ping_cm();
    delay(2);
    if ((dist > 0) && (dist < 50)) {
        dist = 0;
        for (int i = 0; i < 5; i++) {
            dist += sonarside.ping_cm();
            delay(1);
        }
        dist = dist / 5;
    }
    return dist;
}

void steer(int a)
{
    if ((a < MAXANG) && (a > -MAXANG))
        servo.write(STRAIGHT+a);
}

bool lapAnalyze()
{
    static long time = 0;
    static byte numlaps = 0;
    if ((sensorValues[0] > THRESHOLD) && (sensorValues[1] > THRESHOLD) && (sensorValues[2] > THRESHOLD) && (sensorValues[3] > THRESHOLD) && (sensorValues[4] > THRESHOLD) && (sensorValues[5] > THRESHOLD))
    {
        if (numlaps < LAPS)
        {
            numlaps++;
            time = millis();
        }
        else
            return 1;
    }
    if (numlaps >= LAPS)
        return 1;
    return 0;
}

void perpendicularRight()
{
    steer(25);
    delay(190);
    steer(32);
    delay(380);
    steer(0);
}

void perpendicularLeft()
{
    delay(190);
    steer(-32);
    delay(380);
    steer(0);
}
