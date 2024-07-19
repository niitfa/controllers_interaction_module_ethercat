#include "gantry_move_task.h"

void EmulatedGantryMoveTask::StateRun()
{
    if(this->GetMasterTelemetry()->is_drive_enabled)
    { 
        auto props = this->GetContext()->GetSubsystem()->GetProperties();
        float ratio = props.microstep_resolution * props.gear_ratio / kDegreesPerRotation;
        /* Сохраняем позицию в предыдущем такте */
        int32_t previous_position_deg = this->GetMasterTelemetry()->drive_position_deg;
        int32_t previous_position_count = this->GetMasterTelemetry()->drive_position_pulse;
        /* Подготавливаем нужные величины */
        uint32_t frequency = this->GetContext()->GetSubsystem()->GetEthercatConfig()->GetTimer()->GetFrequency();
        int32_t target_position_count = this->target_position_deg * ratio;
        int32_t target_velocity_count_per_sec = this->target_velocity_deg_per_sec * ratio;
        int dir = (this->target_position_deg - this->GetMasterTelemetry()->drive_position_deg > 0)
            - (this->target_position_deg - this->GetMasterTelemetry()->drive_position_deg < 0);
        float delta_position_per_cycle_deg = dir * this->target_velocity_deg_per_sec / frequency;
  
        /* Обновляем телеметрию */
        this->GetMasterTelemetry()->drive_position_deg += delta_position_per_cycle_deg;
        this->GetMasterTelemetry()->drive_position_pulse = this->GetMasterTelemetry()->drive_position_deg * ratio;

        /* После обновления телеметрии рассчитываем скорости */
        this->GetMasterTelemetry()->drive_velocity_deg_per_sec = delta_position_per_cycle_deg * frequency;
        this->GetMasterTelemetry()->drive_velocity_pulse_per_sec = (this->GetMasterTelemetry()->drive_position_pulse - previous_position_count) * frequency;

        /* Условие завершения задания */
        if(std::abs(target_position_deg - this->GetMasterTelemetry()->drive_position_deg) < std::abs(2 * delta_position_per_cycle_deg))
        {
            this->GetMasterTelemetry()->drive_position_deg = target_position_deg;
            this->GetMasterTelemetry()->drive_position_pulse = target_position_count;
            this->GetMasterTelemetry()->drive_velocity_deg_per_sec = 0;
            this->GetMasterTelemetry()->drive_velocity_pulse_per_sec = 0;
            GantryTaskState::GetContext()->TransitToNext();
        }
    }
    else
    {
        GantryTaskState::GetContext()->TransitToNext();
    }

}