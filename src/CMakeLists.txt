# CMake file for DISTRHO Plugins #
# ------------------------------ #

dpf_add_plugin(d_bits
  TARGETS ladspa lv2 vst2
  FILES_DSP
      bits.cpp)

target_include_directories(
  d_bits PUBLIC ".")
