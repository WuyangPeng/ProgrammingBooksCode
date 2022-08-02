#pragma once

namespace Bad
{
    class Command;
    class Report;

    // 展现不良抽象的类接口
    class Program
    {
    public:
        void InitializeCommandStack();
        void PushCommand();
        Command PopCommand();
        void FormatReport(Report report);
        void PrintReport(Report report);
        void InitializeGlobalData();
        void ShutdownGlobalData();

    private:
    };
}

namespace Good
{
    // 能更好展现抽象的类接口
    class Program
    {
    public:
        void InitializeUserInterface();
        void ShutdownUserInterface();
        void InitializeReports();
        void ShutDownReports();

    private:
    };
}