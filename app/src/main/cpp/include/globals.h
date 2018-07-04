#ifndef FLAPPYBIRDANDROID_GLOBALS_H
#define FLAPPYBIRDANDROID_GLOBALS_H

#define DELETE_PTR(x) if(x != nullptr)	        \
                        {                   \
                            delete x;       \
                            x = nullptr;    \
                        }
#define DELETE_PTR_ARRAY(x) if(x != nullptr)           \
                                {                   \
                                    delete[] x;     \
                                    x = nullptr;    \
                                }

#define PROPERTIES_PATH "data/properties.data"
#define SCOREFILE_PATH "config/config.data"

#endif //FLAPPYBIRDANDROID_GLOBALS_H
