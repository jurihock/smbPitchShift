#pragma once

#include <memory>
#include <span>
#include <tuple>
#include <vector>

#include <StftPitchShift/FFT.h>

namespace stftpitchshift
{
  /**
   * Short-time Fourier transform (STFT) based pitch shifting.
   */
  class StftPitchShift
  {

  public:

    /**
     * @param samplerate The sample rate of the signal in hertz.
     * @param framesize The STFT frame size in samples (analysis = synthesis).
     * @param hopsize The STFT hop size in samples.
     * @param padsize The FFT zero padding factor.
     * @param normalization Optionally enable spectral rms normalization.
     * @param chronometry Optionally enable runtime measurements.
     */
    StftPitchShift(
      const double samplerate,
      const size_t framesize,
      const size_t hopsize,
      const size_t padsize = 1,
      const bool normalization = false,
      const bool chronometry = false);

    /**
     * @param samplerate The sample rate of the signal in hertz.
     * @param framesize The STFT frame size in samples (analysis >= synthesis).
     * @param hopsize The STFT hop size in samples.
     * @param padsize The FFT zero padding factor.
     * @param normalization Optionally enable spectral rms normalization.
     * @param chronometry Optionally enable runtime measurements.
     */
    StftPitchShift(
      const double samplerate,
      const std::tuple<size_t, size_t> framesize,
      const size_t hopsize,
      const size_t padsize = 1,
      const bool normalization = false,
      const bool chronometry = false);

    /**
     * @param fft The custom FFT calculation instance.
     * @param samplerate The sample rate of the signal in hertz.
     * @param framesize The STFT frame size in samples (analysis = synthesis).
     * @param hopsize The STFT hop size in samples.
     * @param padsize The FFT zero padding factor.
     * @param normalization Optionally enable spectral rms normalization.
     * @param chronometry Optionally enable runtime measurements.
     */
    StftPitchShift(
      const std::shared_ptr<FFT> fft,
      const double samplerate,
      const size_t framesize,
      const size_t hopsize,
      const size_t padsize = 1,
      const bool normalization = false,
      const bool chronometry = false);

    /**
     * @param fft The custom FFT calculation instance.
     * @param samplerate The sample rate of the signal in hertz.
     * @param framesize The STFT frame size in samples (analysis >= synthesis).
     * @param hopsize The STFT hop size in samples.
     * @param padsize The FFT zero padding factor.
     * @param normalization Optionally enable spectral rms normalization.
     * @param chronometry Optionally enable runtime measurements.
     */
    StftPitchShift(
      const std::shared_ptr<FFT> fft,
      const double samplerate,
      const std::tuple<size_t, size_t> framesize,
      const size_t hopsize,
      const size_t padsize = 1,
      const bool normalization = false,
      const bool chronometry = false);

    /**
     * @param input The input signal.
     * @param output The output signal of the equal size.
     * @param factor The fractional pitch shifting factor.
     * @param quefrency The optional formant lifter quefrency in seconds.
     * @param distortion The fractional timbre shifting factor.
     */
    void shiftpitch(
      const std::span<const float> input,
      const std::span<float> output,
      const double factor = 1,
      const double quefrency = 0,
      const double distortion = 1);

    /**
     * @param input The input signal.
     * @param output The output signal of the equal size.
     * @param factor The fractional pitch shifting factor.
     * @param quefrency The optional formant lifter quefrency in seconds.
     * @param distortion The fractional timbre shifting factor.
     */
    void shiftpitch(
      const std::span<const double> input,
      const std::span<double> output,
      const double factor = 1,
      const double quefrency = 0,
      const double distortion = 1);

    /**
     * @param input The input signal.
     * @param output The output signal of the equal size.
     * @param factors The fractional pitch shifting factors.
     * @param quefrency The optional formant lifter quefrency in seconds.
     * @param distortion The fractional timbre shifting factor.
     */
    void shiftpitch(
      const std::span<const float> input,
      const std::span<float> output,
      const std::vector<double>& factors,
      const double quefrency = 0,
      const double distortion = 1);

    /**
     * @param input The input signal.
     * @param output The output signal of the equal size.
     * @param factors The fractional pitch shifting factors.
     * @param quefrency The optional formant lifter quefrency in seconds.
     * @param distortion The fractional timbre shifting factor.
     */
    void shiftpitch(
      const std::span<const double> input,
      const std::span<double> output,
      const std::vector<double>& factors,
      const double quefrency = 0,
      const double distortion = 1);

  private:

    const std::shared_ptr<FFT> fft;
    const double samplerate;
    const std::tuple<size_t, size_t> framesize;
    const size_t hopsize;
    const size_t padsize;
    const bool normalization;
    const bool chronometry;

  };
}
