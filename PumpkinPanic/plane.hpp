#pragma once

#include <stdint.h>

static const vertex_t plane_vertices[] = {
    // +Y
    {.position = {-1.f,  1.f, -1.f}, .texcoord = {0.f, 0.f}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    {.position = {-1.f,  1.f,  1.f}, .texcoord = {0.f, 1.f}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    {.position = { 1.f,  1.f,  1.f}, .texcoord = {1.f, 1.f}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    {.position = { 1.f,  1.f, -1.f}, .texcoord = {1.f, 0.f}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
};

static const uint16_t plane_indices[] = {
     0,  1,  2,  0,  2,  3,
};
