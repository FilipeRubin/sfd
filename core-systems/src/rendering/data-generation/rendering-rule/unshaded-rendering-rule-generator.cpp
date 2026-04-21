#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>

IRenderingRuleGenerator::Type UnshadedRenderingRuleGenerator::GetType() const
{
    return Type::UNSHADED;
}
