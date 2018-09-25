uint16_t uiLedTm = 0;
enLedState = 0u;


void main (void)
{
    fnvConfigTimer();
    
    fnvConfigIntExt();
    
    while (1)
    {
        fnvLedCtrl();
        fnvInputsDeb();
    }

}


void fnvLedCtrl(void)
{
    if (uiLedTm == 0)
    {
        switch (enLedState)
        {
            /*IDLE - Sempre desligado.*/
            case 0:
            {
                LED desligado;
            }
            break;
            case 1:
            {
                LED ligado;
                
                uiLedTm = 1000;
                
                enLedState = 2;
            }
            break;
            case 2:
            {
                enLedState = 0;
            }
        }
    }
}


void fnvTimerHandler (void)
{
    if (uiLedTm != 0)
    {
        uiLedTm--;
    }
    
    if (uiInDebTm != 0)
    {
        uiInDebTm--;
    }
}


void fnvIntExtHandler (void)
{
    if (enLedState == 0)
    {
        enLedState = 1;
    }
}

uint8_t ucIgnDebCnt;
uint8_t ucIgnPrevValue;
uint8_t ucIgnValue;


void fnvInputDeb()
{
    if (uiInDebTm == 0u)
    {
        uiInDebTm = 10u;
        
        
        
    }
}
