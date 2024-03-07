
#include "DecalResource.hh"
#include "olcPixelGameEngine.h"

namespace pge {

void DecalResource::DecalDeleter::operator()(olc::Decal *decal) const noexcept
{
  if (!decal)
  {
    return;
  }

  if (nullptr != decal->sprite)
  {
    delete decal->sprite;
    decal->sprite = nullptr;
  }

  delete decal;
}

DecalResource::DecalResource(const std::string &fileName)
{
  auto sprite = new olc::Sprite(fileName);
  if (nullptr == sprite)
  {
    throw std::invalid_argument("Failed to create decal from \"" + fileName + "\"");
  }

  m_decal = std::unique_ptr<olc::Decal, DecalDeleter>(new olc::Decal(sprite));
}

DecalResource::DecalResource(olc::Decal *decal)
{
  if (nullptr == decal)
  {
    throw std::invalid_argument("Expected non null decal resource");
  }
  if (nullptr == decal->sprite)
  {
    throw std::invalid_argument("Expected non null sprite resource");
  }

  m_decal = std::unique_ptr<olc::Decal, DecalDeleter>(decal);
}

auto DecalResource::get() const -> olc::Decal *
{
  return m_decal.get();
}

auto DecalResource::w() const -> int
{
  return m_decal->sprite->width;
}

auto DecalResource::h() const -> int
{
  return m_decal->sprite->height;
}

} // namespace pge
