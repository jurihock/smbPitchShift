#include <StftPitchShift/StftPitchShift.h>

#include <StftPitchShift/Cepster.h>
#include <StftPitchShift/Pitcher.h>
#include <StftPitchShift/STFT.h>
#include <StftPitchShift/Vocoder.h>

StftPitchShift::StftPitchShift(
  const size_t framesize,
  const size_t hopsize,
  const double samplerate,
  const bool chronometry) :
  fft(std::make_shared<Pocketfft>()),
  framesize(framesize),
  hopsize(hopsize),
  samplerate(samplerate),
  chronometry(chronometry)
{
}

StftPitchShift::StftPitchShift(
  const std::shared_ptr<FFT> fft,
  const size_t framesize,
  const size_t hopsize,
  const double samplerate,
  const bool chronometry) :
  fft(fft),
  framesize(framesize),
  hopsize(hopsize),
  samplerate(samplerate),
  chronometry(chronometry)
{
}

void StftPitchShift::shiftpitch(
  const std::vector<float>& input,
  std::vector<float>& output,
  const double factor,
  const double quefrency)
{
  const std::vector<double> factors = { factor };

  shiftpitch(
    input.size(),
    input.data(),
    output.data(),
    factors,
    quefrency);
}

void StftPitchShift::shiftpitch(
  const size_t size,
  const float* input,
  float* const output,
  const double factor,
  const double quefrency)
{
  const std::vector<double> factors = { factor };

  shiftpitch(
    size,
    input,
    output,
    factors,
    quefrency);
}

void StftPitchShift::shiftpitch(
  const std::vector<float>& input,
  std::vector<float>& output,
  const std::vector<double>& factors,
  const double quefrency)
{
  shiftpitch(
    input.size(),
    input.data(),
    output.data(),
    factors,
    quefrency);
}

void StftPitchShift::shiftpitch(
  const size_t size,
  const float* input,
  float* const output,
  const std::vector<double>& factors,
  const double quefrency)
{
  STFT stft(fft, framesize, hopsize, chronometry);
  Vocoder<float> vocoder(framesize, hopsize, samplerate);
  Pitcher<float> pitcher(factors);
  Cepster<float> cepster(fft, quefrency, samplerate);

  if (quefrency)
  {
    std::vector<float> envelope;

    stft(size, input, output, [&](std::vector<std::complex<float>>& frame)
    {
      vocoder.encode(frame);

      cepster.lifter(frame, envelope);

      for (size_t i = 0; i < frame.size(); ++i)
      {
        frame[i].real(frame[i].real() / envelope[i]);
      }

      pitcher.shiftpitch(frame);

      for (size_t i = 0; i < frame.size(); ++i)
      {
        frame[i].real(frame[i].real() * envelope[i]);
      }

      vocoder.decode(frame);
    });
  }
  else
  {
    stft(size, input, output, [&](std::vector<std::complex<float>>& frame)
    {
      vocoder.encode(frame);
      pitcher.shiftpitch(frame);
      vocoder.decode(frame);
    });
  }
}
