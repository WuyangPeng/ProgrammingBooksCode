/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#include "custom_time.h"
#include "profile.h"
#include "text.h"
#include <cassert>
#include <cstdio>
#include <cstring>

typedef struct
{
    bool bValid;  //Whether this data is valid 数据是否有效
    unsigned int iProfileInstances;  //# of times ProfileBegin called ProfileBegin调用次数
    int iOpenProfiles;  //# of times ProfileBegin w/o ProfileEnd 没有相匹配ProfileEnd调用的ProfileBegin调用次数
    char szName[256];  //Name of sample 样本名称
    float fStartTime;  //The current open profile start time 当前样本开始时间
    float fAccumulator;  //All samples this frame added together 帧内所有样本总计
    float fChildrenSampleTime;  //Time taken by all children 所有子样本耗时
    unsigned int iNumParents;  //Number of profile parents 父样本数
} ProfileSample;

typedef struct
{
    bool bValid;  //Whether the data is valid 数据是否有效
    char szName[256];  //Name of the sample 样本名称
    float fAve;  //Average time per frame (percentage) 每帧的平均时间（百分比）
    float fMin;  //Minimum time per frame (percentage) 每帧的最小时间（百分比）
    float fMax;  //Maximum time per frame (percentage) 每帧的最大时间（百分比）
} ProfileSampleHistory;

#define NUM_PROFILE_SAMPLES 50
ProfileSample g_samples[NUM_PROFILE_SAMPLES];
ProfileSampleHistory g_history[NUM_PROFILE_SAMPLES];
float g_startProfile = 0.0f;
float g_endProfile = 0.0f;
TextBox* textBox = 0;

void ProfileInit(void)
{
    unsigned int i;

    for (i = 0; i < NUM_PROFILE_SAMPLES; i++)
    {
        g_samples[i].bValid = false;
        g_history[i].bValid = false;
    }

    g_startProfile = GetExactTime();

    textBox = new TextBox(0, 640, 0, 480);
    textBox->SetMode(TEXT_NONE);
}

void ProfileBegin(const char* name)
{
    unsigned int i = 0;

    while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true)
    {
        if (strcmp(g_samples[i].szName, name) == 0)
        {
            //Found the sample
            // 找到一个样本
            g_samples[i].iOpenProfiles++;
            g_samples[i].iProfileInstances++;
            g_samples[i].fStartTime = GetExactTime();
            assert(g_samples[i].iOpenProfiles == 1);  //max 1 open at once 每次的最大值为1
            return;
        }
        i++;
    }

    if (i >= NUM_PROFILE_SAMPLES)
    {
        assert(!"Exceeded Max Available Profile Samples");
        return;
    }

    strcpy_s(g_samples[i].szName, name);
    g_samples[i].bValid = true;
    g_samples[i].iOpenProfiles = 1;
    g_samples[i].iProfileInstances = 1;
    g_samples[i].fAccumulator = 0.0f;
    g_samples[i].fStartTime = GetExactTime();
    g_samples[i].fChildrenSampleTime = 0.0f;
}

void ProfileEnd(const char* name)
{
    unsigned int i = 0;
    unsigned int numParents = 0;

    while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true)
    {
        if (strcmp(g_samples[i].szName, name) == 0)
        {  //Found the sample
            // 找到一个样本
            unsigned int inner = 0;
            int parent = -1;
            float fEndTime = GetExactTime();
            g_samples[i].iOpenProfiles--;

            //Count all parents and find the immediate parent
            // 统计所有父节点并找到直接父节点
            while (g_samples[inner].bValid == true)
            {
                if (g_samples[inner].iOpenProfiles > 0)
                {  //Found a parent (any open profiles are parents)
                    // 找到一个父节点（任何开放的节点都是父节点）
                    numParents++;
                    if (parent < 0)
                    {  //Replace invalid parent (index)
                        // 替换无效父节点（索引）
                        parent = inner;
                    }
                    else if (g_samples[inner].fStartTime >=
                             g_samples[parent].fStartTime)
                    {  //Replace with more immediate parent
                        // 替换最直接的父节点
                        parent = inner;
                    }
                }
                inner++;
            }

            //Remember the current number of parents of the sample
            // 记录样本父节点当前数量
            g_samples[i].iNumParents = numParents;

            if (parent >= 0)
            {  //Record this time in fChildrenSampleTime (add it in)
                // 记录时间到fChildrenSampleTime（累加）
                g_samples[parent].fChildrenSampleTime += fEndTime -
                                                         g_samples[i].fStartTime;
            }

            //Save sample time in accumulator
            // 保存累及样本时间
            g_samples[i].fAccumulator += fEndTime - g_samples[i].fStartTime;
            return;
        }
        i++;
    }
}

void ProfileDumpOutputToBuffer(void)
{
    unsigned int i = 0;

    g_endProfile = GetExactTime();
    textBox->Clear();

    textBox->Printf("  Ave :   Min :   Max :   # : Profile Name\n");
    textBox->Printf("--------------------------------------------\n");

    while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true)
    {
        unsigned int indent = 0;
        float sampleTime, percentTime, aveTime, minTime, maxTime;
        char line[256], name[256], indentedName[256];
        char ave[16], min[16], max[16], num[16];

        if (g_samples[i].iOpenProfiles < 0)
        {
            assert(!"ProfileEnd() called without a ProfileBegin()");
        }
        else if (g_samples[i].iOpenProfiles > 0)
        {
            assert(!"ProfileBegin() called without a ProfileEnd()");
        }

        sampleTime = g_samples[i].fAccumulator - g_samples[i].fChildrenSampleTime;
        percentTime = (sampleTime / (g_endProfile - g_startProfile)) * 100.0f;

        aveTime = minTime = maxTime = percentTime;

        //Add new measurement into the history and get the ave, min, and max
        // 在历史记录中增加新的测量值，并获取平均、最小和最大值
        StoreProfileInHistory(g_samples[i].szName, percentTime);
        GetProfileFromHistory(g_samples[i].szName, &aveTime, &minTime, &maxTime);

        //Format the data
        // 格式化数据
        sprintf_s(ave, "%3.1f", aveTime);
        sprintf_s(min, "%3.1f", minTime);
        sprintf_s(max, "%3.1f", maxTime);
        sprintf_s(num, "%3d", g_samples[i].iProfileInstances);

        strcpy_s(indentedName, g_samples[i].szName);
        for (indent = 0; indent < g_samples[i].iNumParents; indent++)
        {
            sprintf_s(name, "   %s", indentedName);
            strcpy_s(indentedName, name);
        }

        sprintf_s(line, "%5s : %5s : %5s : %3s : %s\n", ave, min, max, num, indentedName);
        textBox->Printf(line);  //Send the line to text buffer 将当前行写入文本缓冲区
        i++;
    }

    {  //Reset samples for next frame
        // 为下一帧重置样本数据

        for (i = 0; i < NUM_PROFILE_SAMPLES; i++)
        {
            g_samples[i].bValid = false;
        }
        g_startProfile = GetExactTime();
    }
}

void StoreProfileInHistory(char* name, float percent)
{
    unsigned int i = 0;
    float oldRatio;
    float newRatio = 0.8f * GetElapsedTime();
    if (newRatio > 1.0f)
    {
        newRatio = 1.0f;
    }
    oldRatio = 1.0f - newRatio;

    while (i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true)
    {
        if (strcmp(g_history[i].szName, name) == 0)
        {  //Found the sample
            // 找到一个样本
            g_history[i].fAve = (g_history[i].fAve * oldRatio) + (percent * newRatio);
            if (percent < g_history[i].fMin)
            {
                g_history[i].fMin = percent;
            }
            else
            {
                g_history[i].fMin = (g_history[i].fMin * oldRatio) + (percent * newRatio);
            }

            if (g_history[i].fMin < 0.0f)
            {
                g_history[i].fMin = 0.0f;
            }

            if (percent > g_history[i].fMax)
            {
                g_history[i].fMax = percent;
            }
            else
            {
                g_history[i].fMax = (g_history[i].fMax * oldRatio) + (percent * newRatio);
            }
            return;
        }
        i++;
    }

    if (i < NUM_PROFILE_SAMPLES)
    {  //Add to history
        // 添加到历史数据
        strcpy_s(g_history[i].szName, name);
        g_history[i].bValid = true;
        g_history[i].fAve = g_history[i].fMin = g_history[i].fMax = percent;
    }
    else
    {
        assert(!"Exceeded Max Available Profile Samples!");
    }
}

void GetProfileFromHistory(char* name, float* ave, float* min, float* max)
{
    unsigned int i = 0;
    while (i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true)
    {
        if (strcmp(g_history[i].szName, name) == 0)
        {  //Found the sample
            // 找到一个样本
            *ave = g_history[i].fAve;
            *min = g_history[i].fMin;
            *max = g_history[i].fMax;
            return;
        }
        i++;
    }
    *ave = *min = *max = 0.0f;
}

void ProfileDraw(void)
{
    if (textBox)
    {
        //textBox->Printf( "Yippee Yahoo!!!\n" );
        textBox->Draw();
    }
}
