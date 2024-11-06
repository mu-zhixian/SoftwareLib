
int main(){
    HAL_Init();
    ClockConf();
    DeviceIO_Conf();
    UartConf();
    TimerConf();
    printf("Hello World!\r\n");
    while(1){
        if(GetNotEmpty(&hrq)){
            printf("%s\r\n", GetDequeuePos(&hrq));
            //Because GetDequeueNums() controls pointer dequeue ,you have to call it!
            printf("Output:%d\r\n", GetDequeueNums(&hrq));
        }
    }
}

void USART1_IRQHandler(void){
  HAL_UART_IRQHandler(&huart1);
  UartIDLE_Callback(&huart1);
}

void UartIDLE_Callback(UART_HandleTypeDef *huart){
    if(huart == &huart1){
        if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)){
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            GetTransCount(&hrq, huart->RxXferCount);
            HAL_UART_AbortReceive_IT(huart);
        }
    }
}

void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart){
    if(huart == &huart1){
        CallbackDispose(&hrq);
        //Because HAL_UART_IRQHandler() will turn off the interrupt!
        HAL_UART_Receive_IT(&huart1, GetEnqueuePos(&hrq), TransSize);
    }
}

int fputc(int ch, FILE *f){
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xffff);
    return ch;
}

//Uart config!
void UartConf(){
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&huart1);

    RingQueueInit(&hrq);

    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_IT(&huart1, GetEnqueuePos(&hrq), TransSize);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){
    GPIO_InitTypeDef GPIO_InitType = {0};
    if(huart->Instance==USART1){
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_AFIO_CLK_ENABLE();
        __HAL_AFIO_REMAP_USART1_ENABLE();
        GPIO_InitType.Pin = GPIO_PIN_6;
        GPIO_InitType.Mode = GPIO_MODE_AF_PP;
        GPIO_InitType.Speed = GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(GPIOB, &GPIO_InitType);
        GPIO_InitType.Pin = GPIO_PIN_7;
        GPIO_InitType.Mode = GPIO_MODE_AF_INPUT;
        GPIO_InitType.Pull = GPIO_NOPULL; 
        HAL_GPIO_Init(GPIOB, &GPIO_InitType);
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}
