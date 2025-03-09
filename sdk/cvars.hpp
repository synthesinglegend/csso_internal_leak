#pragma once

class convar
{
public:
    void SetValue(const char* value)
    {
        typedef void(__thiscall* fn)(void*, const char*);
        vfunc<fn>(this, 10)(this, value);
    }
    void SetValue(float value)
    {
        typedef void(__thiscall* fn)(void*, float);
        vfunc<fn>(this, 11)(this, value);
    }
    void SetValue(int value)
    {
        typedef void(__thiscall* fn)(void*, int);
        vfunc<fn>(this, 12)(this, value);
    }

    float GetFloat()
    {
        return m_fValue;
    }
    int GetInt()
    {
        return m_nValue;
    }

public:
    float m_fValue;
    int m_nValue;
};

class icvar {
public:
    convar* FindVar(const char* var)
    {
        typedef convar* (__thiscall* fn)(void*, const char*);
        return vfunc<fn>(this, 13)(this, var);
    }
};
