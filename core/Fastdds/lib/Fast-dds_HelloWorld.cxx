/*!
 * @file HelloWorld.cpp
*/

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "../include/Fast-dds_HelloWorld.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define HelloWorld_max_cdr_typesize 264ULL;
#define HelloWorld_max_key_cdr_typesize 0ULL;

HelloWorld::HelloWorld()
{
    // unsigned long m_index
    m_index = 0;
    // string m_message
    m_message ="";

}

HelloWorld::~HelloWorld()
{


}

HelloWorld::HelloWorld(
        const HelloWorld& x)
{
    m_index = x.m_index;
    m_message = x.m_message;
}

HelloWorld::HelloWorld(
        HelloWorld&& x) noexcept 
{
    m_index = x.m_index;
    m_message = std::move(x.m_message);
}

HelloWorld& HelloWorld::operator =(
        const HelloWorld& x)
{

    m_index = x.m_index;
    m_message = x.m_message;

    return *this;
}

HelloWorld& HelloWorld::operator =(
        HelloWorld&& x) noexcept
{

    m_index = x.m_index;
    m_message = std::move(x.m_message);

    return *this;
}

bool HelloWorld::operator ==(
        const HelloWorld& x) const
{

    return (m_index == x.m_index && m_message == x.m_message);
}

bool HelloWorld::operator !=(
        const HelloWorld& x) const
{
    return !(*this == x);
}

size_t HelloWorld::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return HelloWorld_max_cdr_typesize;
}

size_t HelloWorld::getCdrSerializedSize(
        const HelloWorld& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.message().size() + 1;


    return current_alignment - initial_alignment;
}

void HelloWorld::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_index;
    scdr << m_message.c_str();

}

void HelloWorld::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_index;
    dcdr >> m_message;
}

/*!
 * @brief This function sets a value in member index
 * @param _index New value for member index
 */
void HelloWorld::index(
        uint32_t _index)
{
    m_index = _index;
}

/*!
 * @brief This function returns the value of member index
 * @return Value of member index
 */
uint32_t HelloWorld::index() const
{
    return m_index;
}

/*!
 * @brief This function returns a reference to member index
 * @return Reference to member index
 */
uint32_t& HelloWorld::index()
{
    return m_index;
}

/*!
 * @brief This function copies the value in member message
 * @param _message New value to be copied in member message
 */
void HelloWorld::message(
        const std::string& _message)
{
    m_message = _message;
}

/*!
 * @brief This function moves the value in member message
 * @param _message New value to be moved in member message
 */
void HelloWorld::message(
        std::string&& _message)
{
    m_message = std::move(_message);
}

/*!
 * @brief This function returns a constant reference to member message
 * @return Constant reference to member message
 */
const std::string& HelloWorld::message() const
{
    return m_message;
}

/*!
 * @brief This function returns a reference to member message
 * @return Reference to member message
 */
std::string& HelloWorld::message()
{
    return m_message;
}


size_t HelloWorld::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return HelloWorld_max_key_cdr_typesize;
}

bool HelloWorld::isKeyDefined()
{
    return false;
}

void HelloWorld::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}
