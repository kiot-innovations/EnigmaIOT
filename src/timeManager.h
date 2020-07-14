/**
  * @file timeManager.h
  * @version 0.9.3
  * @date 14/07/2020
  * @author German Martin
  * @brief Clock synchronisation calculations
  */

#ifndef _TIMEMANAGER_h
#define _TIMEMANAGER_h

#include <Arduino.h>

class TimeManagerClass {
protected:
    //clock_t t1, t2, t3, t4;
    bool timeIsAdjusted = false; ///< @brief Indicates if time has been synchronized
    int64_t offset = 0; ///< @brief Offet between node `millis()` and gateway time
    int64_t roundTripDelay; ///< @brief Propagation delay between Node and Gateway

public:
    /**
      * @brief Inits time synchronization getting local clock to be assigned to T1
      * @return Value of T1
      */
    int64_t setOrigin ();

    /**
      * @brief Gets local clock. It returns `millis()` if not synchronized, local clock otherwise.
      * @return Clock value in ms
      */
    int64_t clock ();

    /**
      * @brief Gets local clock in seconds. It returns `millis() / 1000` if not synchronized, local clock otherwise.
      *         This may contain current realtime clock if Gateway is synchronized using NTP time.
      * @return Clock value in seconds. It uses UnixTime format
      */
    time_t unixtime () {
        uint64_t time_sec = clock () / 1000;
        return time_sec;
    }

     /**
      * @brief Gets delay between Gateway time and local clock and adjust local clock accordingly. It uses same procedure as SNTP protocol.
      * @param t1r T1
      * @param t2r T2
      * @param t3r T3
      * @param t4r T4
      * @return Clock value in seconds. It uses UnixTime format
      */
    int64_t adjustTime (int64_t t1r, int64_t t2r, int64_t t3r, int64_t t4r);

    /**
      * @brief Gets current offset to calculate clock, in milliseconds.
      * @return Offset value in ms
      */
    int64_t getOffset () {
        return offset;
    }

    /**
      * @brief Gets synchronization status
      * @return `True` if clock is synchronized
      */
    bool isTimeAdjusted () {
        return timeIsAdjusted;
    }

    /**
      * @brief Gets propagation + processing delay between Node and Gateway in milliseconds.
      * @return Delay value in ms
      */
    int64_t getDelay () {
        return roundTripDelay;
    }

    /**
      * @brief Resets clock synchronization and sets values to initial status
      */
	void reset () {
		offset = 0;
		timeIsAdjusted = false;
	}
};

extern TimeManagerClass TimeManager;

#endif

