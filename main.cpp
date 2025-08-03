#include <iostream>
#include <vector>
#include "QueueControl.h"
#include "OutputDriver.h"
#include "InputInterface.h"

using namespace std;

int main(){
    QueueControl* queueControl = new QueueControl();
    CountRef * count = queueControl->getInstance()->getCountRef();
    OutputDriver* outputDriver = new OutputDriver(count);
    InputInterface* inputInterface = new InputInterface();
    inputInterface->setQueue(queueControl->getQueue());

    inputInterface->runInputInterface();
    queueControl->popEventAndAssignThreadPoolWithMem();
    outputDriver->flushOutput();
    
    return 0;

}
