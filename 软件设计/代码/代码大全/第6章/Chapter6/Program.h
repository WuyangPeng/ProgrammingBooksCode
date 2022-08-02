#pragma once

namespace Bad
{
    class Command;
    class Report;

    // չ�ֲ����������ӿ�
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
    // �ܸ���չ�ֳ������ӿ�
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