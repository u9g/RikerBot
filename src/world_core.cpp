#include "world_core.hpp"

namespace rkr {

WorldCore::WorldCore(PluginLoader& ploader, bool ownership) :
    PluginBase("rkr::WorldCore *") {

  ploader.provide("World", this, ownership);
  auto ev = static_cast<EventCore *>(ploader.require("Event"));

  ev->register_callback("ClientboundMapChunk",
      [&](EventCore::ev_id_type ev_id, const void* data) {
      chunk_update(ev_id, data);});

  ev->register_callback("ClientboundUnloadChunk",
      [&](EventCore::ev_id_type ev_id, const void* data) {
      chunk_unload(ev_id, data);});
}

void WorldCore::chunk_update(EventCore::ev_id_type ev_id, const void* data) {
  auto packet = static_cast<const mcd::ClientboundMapChunk*>(data);
  world.update(*packet);
}

void WorldCore::chunk_unload(EventCore::ev_id_type ev_id, const void* data) {
  auto packet = static_cast<const mcd::ClientboundUnloadChunk*>(data);
  world.unload(*packet);
}

} //namespace rkr