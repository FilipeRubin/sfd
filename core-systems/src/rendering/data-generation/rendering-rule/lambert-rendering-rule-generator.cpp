#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>

IRenderingRuleGenerator::Type LambertRenderingRuleGenerator::GetType() const
{
    return Type::LAMBERT;
}
