<template>
    <div>
        <div class="status" v-bind:class="{off:!schedule.Arm}"><div class="bullet"></div></div>
        <div class="time">{{schedule.Time}} </div>
        <div class="days">
            <span v-for="(day, key) in days" :key="key" class="grey-text" 
            v-bind:class="{'text-darken-4':schedule.Days[key]==1}">
            {{day}}
            </span>
        </div>
        <div class="mode">{{modeStr}}</div>
        <div class="spacer"></div>
        <div class="switch right"><label><input type="checkbox" v-model="schedule.Arm" @change="saveSchedule()"><span class="lever"></span></label></div>
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
            var data = JSON.parse(JSON.stringify(this.schedule)); // clone
            data.Days = stringNumbers;
        
            Service.saveTimer(data, this.timerId);
        },
    },
    computed: {
        modeStr() {
            if (this.schedule.Mode == 0)
                return "Time";
            else if (this.schedule.Mode == 1)
                return "Sunrise";
            else if (this.schedule.Mode == 2)
                return "Sunset";
            else if (this.schedule.Mode == 3)
                return "Cost Optimizer";
        }
    },
    mounted(){
    }
}
</script>

<style scoped>
.status>.bullet{
  border-radius: 50%;
  width: 15px;
  height: 15px;
  margin: 5px;
  background-color: rgb(8, 252, 8);
  box-shadow: 0 0 8px rgb(11, 255, 11);
}

.status.on>.bullet {
  
}

.status.off>.bullet {
  background-color: rgb(255, 0, 0);
  box-shadow: 0 0 8px rgb(255, 11, 11);
}

.time{
  font-size: 1.3em;
  margin: 0 10px;
}

.spacer{
  flex-grow: 1;
}

.days {
  margin: 0 10px;
  padding: 6px 0;
  font-size: 0.8em;
}

.header-container{
    justify-content:space-between;
}
</style>
