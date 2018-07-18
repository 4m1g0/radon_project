<template>
    <div>
        <div class="row">
            <div class="input-field col s4" id="schedule-time">
                <input v-model="schedule.Time" type="text" class="timepicker"  @change="saveSchedule()">
                <label>Time</label>
            </div>
            <div class="hidden">{{modeStr}}</div>
            <div class="input-field col s4" id="schedule-mode">
                <select v-model="schedule.Mode" @change="saveSchedule()">
                    <option value="3">Cost Optimizer</option>
                    <option value="0">Time</option>
                    <option value="1">Sunrise</option>
                    <option value="2">Sunset</option>
                </select>
                <label>Mode</label>
            </div>
            <div v-show="schedule.Mode!=3" class="input-field col s4" id="schedule-action">
                <select v-model="schedule.Action" @change="saveSchedule()">
                    <option value="0">Off</option>
                    <option value="1">On</option>
                    <option value="2">Toggle</option>
                </select>
                <label>Action</label>
            </div>
            <!-- interval -->
            <div v-show="schedule.Mode==3" class="input-field col s2" id="schedule-window">
                <select v-model="schedule.Window" @change="saveSchedule()">
                    <option value="0">2</option>
                    <option value="1">3</option>
                    <option value="2">4</option>
                    <option value="3">5</option>
                    <option value="4">6</option>
                    <option value="5">7</option>
                    <option value="6">8</option>
                    <option value="7">9</option>
                    <option value="8">10</option>
                    <option value="9">11</option>
                    <option value="10">12</option>
                    <option value="11">13</option>
                    <option value="12">14</option>
                    <option value="13">15</option>
                    <option value="14">16</option>
                    <option value="15">17</option>
                    <option value="16">18</option>
                    <option value="17">19</option>
                    <option value="18">20</option>
                    <option value="19">21</option>
                    <option value="20">22</option>
                    <option value="21">23</option>
                    <option value="22">24</option>
                </select>
                <label>Interval</label>
            </div>
            <!-- TODO: Action  -->
            <div v-show="schedule.Mode==3" class="input-field col s2" id="schedule-output">
                <select v-model="schedule.Output" @change="saveSchedule()">
                    <option value="1">1</option>
                    <option value="2">2</option>
                    <option value="3">3</option>
                    <option value="4">4</option>
                    <option value="5">5</option>
                    <option value="6">6</option>
                    <option value="7">7</option>
                    <option value="8">8</option>
                    <option value="9">9</option>
                    <option value="10">10</option>
                    <option value="11">11</option>
                    <option value="12">12</option>
                    <option value="13">13</option>
                    <option value="14">14</option>
                    <option value="15">15</option>
                    <option value="16">16</option>
                    <option value="17">17</option>
                </select>
                <label>Duration</label>
            </div>
        </div>
        <div>
            <label class="day-check" v-for="(day, key) in days" :key="key">
            <input type="checkbox" class="filled-in" v-model="schedule.Days[key]" @change="saveSchedule()" />
            <span>{{day}}</span>
            </label>
        </div>
    </div>
</template>

<script>
import Service from './Service'

export default {
    props: ['schedule', 'timerId'],
    data: function(){
        return {
            days: ['S','M','T','W','T','F','S'],
        };
    },
    methods: {
        saveSchedule(){
            if (this.schedule.Arm == true || this.schedule.Arm == 1)
                this.schedule.Arm = 1;
            else
                this.schedule.Arm = 0;

            var arrayBool = this.schedule.Days;
            var stringNumbers = '';
            for (var j=0;j<arrayBool.length;j++){
                if (arrayBool[j]){
                    stringNumbers += 1;
                } else {
                    stringNumbers += 0;
                }
            }
            
            this.schedule.Output = parseInt(this.schedule.Output);
            this.schedule.Window = parseInt(this.schedule.Window);
            var time = document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].value;
            if (time.substring(6,8) == "PM") {
                var hour = parseInt(time.substring(0,2)) + 12; // convert to 24h format
                if (hour == 24) hour = "00";
                this.schedule.Time = hour + time.substring(2,5);
            } else {
                this.schedule.Time = time.substring(0,5); // Remove "AM"
            }

            if (this.schedule.Mode == 1 || this.schedule.Mode == 2) {
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].value = "00:00";
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].disabled = true;
            }
            else {
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].disabled = false;
            }


            var data = JSON.parse(JSON.stringify(this.schedule)); // clone
            data.Days = stringNumbers;
        
            Service.saveTimer(data, this.timerId);
        },
        fillSelects(){
            document.querySelectorAll('#schedule-mode')[this.timerId].getElementsByTagName("input")[0].value = this.modeStr;
            document.querySelectorAll('#schedule-output')[this.timerId].getElementsByTagName("input")[0].value = this.schedule.Output;
            document.querySelectorAll('#schedule-window')[this.timerId].getElementsByTagName("input")[0].value = this.schedule.Window + 2;
            document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].value = this.schedule.Time;

            if (this.schedule.Mode == 1 || this.schedule.Mode == 2) {
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].value = "00:00";
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].disabled = true;
            }
            else {
                document.querySelectorAll('#schedule-time')[this.timerId].getElementsByTagName("input")[0].disabled = false;
            }
        }
    },
    computed: {
        modeStr() {
            // eslint-disable-next-line
            setTimeout(this.fillSelects, 0);
            if (this.schedule.Mode == 0)
                return "Time";
            else if (this.schedule.Mode == 1)
                return "Sunrise";
            else if (this.schedule.Mode == 2)
                return "Sunset";
            else if (this.schedule.Mode == 3)
                return "Cost Optimizer";
        },
    },
    mounted(){
        
      document.addEventListener('DOMContentLoaded', function() {
        var elems = document.querySelectorAll('select');
        // eslint-disable-next-line
        M.FormSelect.init(elems, {});
        
      });
      document.addEventListener('DOMContentLoaded', function() {
        var elems = document.querySelectorAll('.timepicker');
        // eslint-disable-next-line
        M.Timepicker.init(elems, {});
      });

      //setTimeout(this.setMode, 500);
    }
}
</script>

<style scoped>

[type="checkbox"] + span:not(.lever){
  padding-left: 25px;
}

.day-check{
  margin: 0 8px;
}

.mode{
  font-size: 1.15em;
  margin: 0 10px;
  padding: 2px 0;
}

.hidden {
    display: none;
}
</style>
