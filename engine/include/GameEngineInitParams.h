#pragma once

class IConfigProvider;

struct EngineInitParams
{
    IConfigProvider* gameLocalConfig;
};