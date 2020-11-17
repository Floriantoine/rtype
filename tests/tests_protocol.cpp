/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** tests_protocol
*/

#include <catch2/catch.hpp>
#include "Protocol.hpp"


TEST_CASE("SerDe success", "[SeDerialization]")
{
    rtype::BPC::Package package;

    package.type = rtype::BPC::REQUEST;
    package.method = rtype::BPC::CREATE;
    package.timestamp = 42;
    auto buffer = rtype::BPC::Serialize(package);
    auto package_b = rtype::BPC::Deserialize(buffer);

    REQUIRE(package.type == package_b.type);
    REQUIRE(package.method == package_b.method);
    REQUIRE(package.timestamp == package_b.timestamp);
    REQUIRE(package.bodySize == package_b.bodySize);
}

TEST_CASE("encode and decode peer infos", "[DeEncodePeerInfos]")
{
    rtype::BPC::Buffer buffer(40);
    rtype::BPC::Endpoint endpoint { "192.168.0.42", 4219 };

    rtype::BPC::EncodePeerInfos(buffer, endpoint);
    auto endpoint_b = rtype::BPC::DecodePeerInfos(buffer);

    REQUIRE(endpoint.ip == endpoint_b.ip);
    REQUIRE(endpoint.port == endpoint_b.port);
}
