#include <string>

// 本子程序将根据调用方子程序所提供的错误码输出对应的错误信息。用于输出信息的方式与当前的
// 处理状态有关，这将由子程序自己来判断。它会返回一个值来表明执行是成功还是失败。

enum Status
{
    Status_Success,
    Status_Failure,
};

enum ErrorCode
{

};

class Message
{
public:
    bool ValidCode() const
    {
        return true;
    }

    std::string Text() const
    {
        return "";
    }
};

Message LookuperrorMessage(ErrorCode errorToReport)
{
    return Message{};
}

enum ProcessingMethod
{
    ProcessingMethod_Interactive,
    ProcessingMethod_CommandLine
};

ProcessingMethod CurrentProcessingMethod()
{
    return ProcessingMethod_Interactive;
}

void DisplayInteractiveMessage(const std::string&)
{
}

enum CommandLineStatus
{
    CommandLineStatus_Ok
};

class CommandLine
{
public:
    CommandLineStatus Status() const
    {
        return CommandLineStatus_Ok;
    }

    void AddToMessageQueue(const std::string&)
    {
    }

    void FlushMessageQueue()
    {
    }
};

Status ReportErrorMessage(ErrorCode errorToReport)
{
    // 设置默认状态为失败
    Status errorMessageStatus = Status_Failure;

    // 根据错误代码查找消息
    Message errorMessage = LookuperrorMessage(errorToReport);

    // 如果错误代码有效
    if (errorMessage.ValidCode())
    {
        // 确定处理方法
        ProcessingMethod errorProcessingMethod = CurrentProcessingMethod();

        // 如果进行交互处理，则交互显示错误消息并声明成功
        if (errorProcessingMethod == ProcessingMethod_Interactive)
        {
            DisplayInteractiveMessage(errorMessage.Text());
            errorMessageStatus = Status_Success;
        }

        // 如果执行命令行处理，则将错误消息记录到命令行并声明成功
        else if (errorProcessingMethod == ProcessingMethod_CommandLine)
        {
            CommandLine messageLog;
            if (messageLog.Status() == CommandLineStatus_Ok)
            {
                messageLog.AddToMessageQueue(errorMessage.Text());
                messageLog.FlushMessageQueue();
                errorMessageStatus = Status_Success;
            }
            else
            {
                // 无法执行任何操作，因为该例程已在错误处理中
            }
        }
        else
        {
            // 无法执行任何操作，因为该例程已在错误处理中
        }
    }

    // 如果错误代码无效，则通知用户已检测到内部错误
    else
    {
        DisplayInteractiveMessage("Internal Error: Invalid error code in ReportErrorMessage()");
    }

    // 返回状态信息
    return errorMessageStatus;
}
