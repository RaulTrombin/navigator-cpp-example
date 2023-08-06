#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

///         Set of available options to select ADC's channel.
enum class AdcChannel {
  Ch0,
  Ch1,
  Ch2,
  Ch3,
};

///         Set of available options to select PWM's channel.
enum class PwmChannel {
  Ch1,
  Ch2,
  Ch3,
  Ch4,
  Ch5,
  Ch6,
  Ch7,
  Ch8,
  Ch9,
  Ch10,
  Ch11,
  Ch12,
  Ch13,
  Ch14,
  Ch15,
  Ch16,
  All,
};

///         Set of options to control navigator's LEDs.
enum class UserLed {
  Led1,
  Led2,
  Led3,
};

///         Encapsulates the value of ADC's four channels.
struct ADCData {
  float channel[4];
};

///         The AxisData encapsulate values for the x, y, and z axes.
struct AxisData {
  float x;
  float y;
  float z;
};

extern "C" {

///         Initialize the navigator module with default settings.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.init()
void init();

///         Runs some tests on available sensors, then returns the result.
///
///        Returns:             bool: The true state means the sensors are OK.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.self_test()
bool self_test();

///         Sets the selected navigator LED output.
///
///        Args:             select (:py:class:`UserLed`):  A pin to be selected.             state (bool): The value of output, LED is on with a true logic value.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import UserLed             >>> navigator.set_led(UserLed.Led1, True)
void set_led(UserLed select,
             bool state);

///         Gets the selected navigator LED output state.
///
///        Args:             select (:py:class:`UserLed`):  A pin to be selected.
///
///        Returns:             bool: The true state means the LED is on.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import UserLed             >>> navigator.get_led(UserLed.Led1)
bool get_led(UserLed select);

///         Toggle the output of selected LED.
///
///        Args:             select (:py:class:`UserLed`):  A pin to be selected.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import UserLed             >>> navigator.set_led_toggle(UserLed.Led1)
void set_led_toggle(UserLed select);

///         Set all LEDs on desired state ( Blue, Green and Red ).
///
///        Args:             state (bool): The value of output, LED is on with a true logic value.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import UserLed             >>> navigator.set_led_all(True)
void set_led_all(bool state);

///No documentation
void set_neopixel(const uint8_t (*rgb_array)[3], uintptr_t length);

///         Reads the ADC based on ADS1115 of Navigator.
///
///        Same as :py:func:`read_adc`, but it returns an array with all channel readings
///
///        Returns:             :py:class:`ADCData`: Measurements in [V].
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.read_adc_all().channel
ADCData read_adc_all();

///         Reads the ADC based on ADS1115 of Navigator.
///
///        Args:             select (:py:class:`AdcChannel`):  A pin to be selected.
///
///        Returns:             float32: Measurements in [V].
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import AdcChannel             >>> navigator.read_adc(AdcChannel.Ch1)
float read_adc(AdcChannel channel);

///         Reads the pressure based on BMP280 of Navigator.
///
///        Returns:             float32: Measurements in [kPa]
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.read_pressure()
float read_pressure();

///         Reads the temperature using BMP280 of Navigator.
///
///        Returns:             float32: Measurements in [˚C]
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.read_temperature()
float read_temp();

///         Reads the magnetometer Ak09915 of Navigator.
///
///        Returns:             :py:class:`AxisData`: Measurements in [µT]
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> AxisData = navigator.read_mag()             >>> AxisData.x             >>> AxisData.y             >>> AxisData.z
AxisData read_mag();

///         Reads acceleration based on ICM20689 of Navigator.
///
///        Returns:             :py:class:`AxisData`: Measurements in [m/s²]
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> AxisData = navigator.read_accel().x             >>> AxisData.x             >>> AxisData.y             >>> AxisData.z
AxisData read_accel();

///         Reads angular velocity based on ICM20689 of Navigator.
///
///        Returns:             :py:class:`AxisData`: Measurements in [rad/s]
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> AxisData = navigator.read_gyro().x             >>> AxisData.x             >>> AxisData.y             >>> AxisData.z
AxisData read_gyro();

///         Sets the PWM IC to be enabled through firmware and OE_pin.
///
///        Args:             state (bool): The state of PWM output, it’s enabled with a true logic value.
///
///        Examples:             Please check :py:func:`set_pwm_channel_value`
///
///            >>> navigator.pwm_enable(True)
void pwm_enable(bool state);

///         Sets the PWM frequency of Navigator.
///
///        It changes the PRE_SCALE value on PCA9685.
///
///        The prescaler value can be calculated for an update rate using the formula:
///
///        prescale_value = round(clock_freq / (4096 * desired_freq)) - 1.
///
///        If you want to control a servo, set a prescaler value of 100. This will correspond to a frequency of about 60 Hz, which is the frequency at which servos work.
///
///        Notes:             Re-run the set_pwm_channel_value() is required.
///
///            The minimum prescaler value is 3, which corresponds to 1526 Hz. The maximum prescaler value is 255, which corresponds to 24 Hz.
///
///            Internally, this function stops the oscillator and restarts it after setting the prescaler value if it was running.
///
///        Args:             value (uint8): The prescaler value (3..255).
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.set_pwm_freq_prescale(100)             >>> navigator.set_pwm_channel_value(PwmChannel.Ch1, 2000)             >>> navigator.pwm_enable(True)
void set_pwm_freq_prescale(uint8_t value);

///             Sets the pwm frequency in Hertz of Navigator. Similar to :py:func:`set_pwm_freq_prescale`.
///
///        Notes:             The navigator module uses a crystal with a 24.5760 MHz clock.
///
///        Args:             freq (float32) : The prescaler value (24..1526)[Hz].
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> navigator.set_pwm_freq_hz(60)             >>> navigator.set_pwm_channel_value(PwmChannel.Ch1, 2000)             >>> navigator.pwm_enable(True)
void set_pwm_freq_hz(float freq);

///         Sets the Duty Cycle (high value time) of selected channel.
///
///        On PCA9685, this function sets the OFF counter and uses ON value as 0.
///
///        Args:             channel (:py:class:`PwmChannel`): The channel to be selected for PWM.             value (u16) : Duty cycle value.
///
///        Examples:             >>> import bluerobotics_navigator as navigator             >>> from bluerobotics_navigator import PwmChannel             >>> navigator.init()             >>> navigator.set_pwm_freq_hz(1000)             >>> navigator.set_pwm_channel_value(PwmChannel.Ch1, 2000)             >>> navigator.pwm_enable(True)
void set_pwm_channel_value(PwmChannel channel,
                           uint16_t value);

///No documentation
void set_pwm_channels_value(const PwmChannel *channels, uint16_t value, uintptr_t length);

///No documentation
void set_pwm_channels_values(const PwmChannel *channels, const uint16_t *values, uintptr_t length);

} // extern "C"
