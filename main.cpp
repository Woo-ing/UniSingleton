#include <cstdio>
#include "UniSingleton.h"

class CPlanet
{
public:
    CPlanet(float radius)
        : m_radius(radius)
    {}

    float radius()
    {
        return m_radius;
    }

protected:
    float m_radius;
};

// Sample for class without instance()
class CSun: public CPlanet
{
public:
    CSun()
    : CPlanet(696300.0f)
    {
    }
};

// Sample for class with instance()
class CEarth :public CPlanet
{
public:
    CEarth()
    : CPlanet(6356.9f)
    {
        singletonMgr.add(this);
    }

    static CEarth& instance()
    {
        static CEarth* sun = new CEarth();
        return *sun;
    }
};

// Sample for TSingleton<_class>
class CMars :public CPlanet
{
public:
    CMars()
    : CPlanet(3376.0f)
    {}
};

typedef TSingleton<CMars> Mars; // Now Mars has instance() and instanceCount()

int main()
{
    auto theSun = the(CSun);
    auto theEarth = the(CEarth);
    auto theMars = the(Mars);   // Use Mars, not CMars

    printf("The radius of Sun is %f\n", theSun.radius());
    printf("The radius of Earth is %f\n", theEarth.radius());
    printf("The radius of Mars is %f\n", theMars.radius());

    // Here's a more advanced usage

    // printf(has(CSun)?"Has Sun":"No Sun");   // Compilation error

    // printf(has(CEarth)?"Has Earth":"No Earth");   // Compilation error

    printf(has(Mars) ? "Has Mars\n" : "No Mars\n");   // Output Has Mars

    if (getThe(Mars) != nullptr)
    {
        delThe(Mars);

        if (getThe(Mars) == nullptr)
            printf("The Mars instance is be removed.\n");
    }

    return 0;
}