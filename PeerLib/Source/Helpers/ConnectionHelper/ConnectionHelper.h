namespace Helpers
{
    template<typename ExceptionT>
    class OperationHelper {
    public:
        template<typename OperationFuncT, typename HandleExceptionFuncT>
        bool static AttemptOperation(
            int maxAttempts,
            DWORD nAttemptTimeoutMs,
            DWORD nConnectionTimeoutMs,
            OperationFuncT operation,
            SOCKET socket,
            sockaddr& pAddr,
            int addrSize,
            HandleExceptionFuncT handleException) 
        {
            for (int count = 0; count < maxAttempts; count++) {
                try {
                    clock_t connStart = clock();
                    for (;;)
                    {
                        clock_t operationCurrent = clock();
                        if (nConnectionTimeoutMs < (operationCurrent - connStart))
                            break;

                        DWORD result = operation(socket, pAddr, addrSize);
                        if (result == -2 || result == -3)
                            continue;
                        if (result == -4)
                            return true;
                        return true;
                    }
                }
                catch (ExceptionT& eT) {
                    handleException(eT);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(nAttemptTimeoutMs));
            }
            return false;
        }
    };
}