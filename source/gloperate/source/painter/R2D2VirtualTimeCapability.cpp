
#include <gloperate/painter/R2D2VirtualTimeCapability.h>

#include <cassert>


namespace gloperate
{


R2D2VirtualTimeCapability::R2D2VirtualTimeCapability()
: m_enabled(true)
, m_duration(-1.0f)
, m_time(0.0f)
, m_delta(0.0f)
{
}

R2D2VirtualTimeCapability::~R2D2VirtualTimeCapability()
{
}

bool R2D2VirtualTimeCapability::enabled() const
{
    return m_enabled;
}

void R2D2VirtualTimeCapability::setEnabled(bool enabled)
{
    m_enabled = enabled;

    setChanged(true);
}

float R2D2VirtualTimeCapability::time() const
{
    return m_time;
}

float R2D2VirtualTimeCapability::delta() const
{
    return m_delta;
}

void R2D2VirtualTimeCapability::setLoopDuration(float duration)
{
    assert(duration > 0.0f);

    m_duration = duration;

    normalizeTime();
}

void R2D2VirtualTimeCapability::update(float delta)
{
    m_time  += delta;
    m_delta  = delta;

    setChanged(true);

    normalizeTime();
}

void R2D2VirtualTimeCapability::normalizeTime()
{
    if (m_duration != -1.0f)
    {
        while (m_time > m_duration)
        {
            m_time -= m_duration;

            setChanged(true);
        }
    }
}


} // namespace gloperate
