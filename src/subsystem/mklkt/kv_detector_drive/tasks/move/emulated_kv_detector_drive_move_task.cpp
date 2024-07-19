#include "kv_detector_drive_move_task.h"

void EmulatedKVDetectorDriveMoveTask::StateRun()
{
    if(this->GetMasterTelemetry()->is_drive_enabled)
    { 
        auto props = this->GetContext()->GetSubsystem()->GetProperties();
        float ratio = props.microstep_resolution / props.thread_pitch;
        /* Сохраняем позицию в предыдущем такте */
        int32_t previous_position_mm = this->GetMasterTelemetry()->drive_position_mm;
        int32_t previous_position_count = this->GetMasterTelemetry()->drive_position_pulse;
        /* Подготавливаем нужные величины */
        uint32_t frequency = this->GetContext()->GetSubsystem()->GetEthercatConfig()->GetTimer()->GetFrequency();
        int32_t target_position_count = this->target_position_mm * ratio;
        int32_t target_velocity_count_per_sec = this->target_velocity_mm_per_sec * ratio;
        int dir = (this->target_position_mm - this->GetMasterTelemetry()->drive_position_mm > 0)
            - (this->target_position_mm - this->GetMasterTelemetry()->drive_position_mm < 0);
        float delta_position_per_cycle_mm = dir * this->target_velocity_mm_per_sec / frequency;
  
        /* Обновляем телеметрию */
        this->GetMasterTelemetry()->drive_position_mm += delta_position_per_cycle_mm;
        this->GetMasterTelemetry()->drive_position_pulse = this->GetMasterTelemetry()->drive_position_mm * ratio;

        /* После обновления телеметрии рассчитываем скорости */
        this->GetMasterTelemetry()->drive_velocity_mm_per_sec = delta_position_per_cycle_mm * frequency;
        this->GetMasterTelemetry()->drive_velocity_pulse_per_sec = (this->GetMasterTelemetry()->drive_position_pulse - previous_position_count) * frequency;

        /* Условие завершения задания */
        if(std::abs(target_position_mm - this->GetMasterTelemetry()->drive_position_mm) < std::abs(2 * delta_position_per_cycle_mm))
        {
            this->GetMasterTelemetry()->drive_position_mm = target_position_mm;
            this->GetMasterTelemetry()->drive_position_pulse = target_position_count;
            this->GetMasterTelemetry()->drive_velocity_mm_per_sec = 0;
            this->GetMasterTelemetry()->drive_velocity_pulse_per_sec = 0;
            KVDetectorDriveTask::GetContext()->TransitToNext();
        }
    }
    else
    {
        KVDetectorDriveTask::GetContext()->TransitToNext();
    }
}