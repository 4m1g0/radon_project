<template>
<div v-bind:style="{minHeight:customHeight*1.4+'px'}">
  <div class="row">
    <div class="col s6">
        <i class="material-icons medium card-panel hoverable power-button" v-bind:class="state?'green-text':'red-text'" @click="toggleSwitch">power_settings_new</i>
    </div>
    <div class="col s6">
      <div class="switch"><label><span v-bind:class="{strong:!state}">Off</span><input type="checkbox" v-model="switch1" @click="toggleSwitch"><span class="lever"></span><span v-bind:class="{strong:state}">On</span></label></div>
    </div>
  </div>
  <div class="card">
    <div class="card-content">
      <div class="row">
        <div class="col m6 s12">
          <span class="card-title right"><nobr>Voltage:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Voltage}} <i class="material-icons">V</i></nobr></span></span>
        </div>
        <div class="col m6 s12">
          <span class="card-title left"><nobr>Power:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Power}} <i class="material-icons">W</i></nobr></span></span>
        </div>
      </div>
      <div class="row">
        <div class="col m6 s12">
          <span class="card-title right"><nobr>Current:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Current}} <i class="material-icons">A</i></nobr></span></span>
        </div>
        <div class="col m6 s12">
          <span class="card-title left"><nobr>Factor:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Factor*100}} <i class="material-icons">%</i></nobr></span></span>
        </div>
      </div>
      <div class="row">
        <div class="col s12">
          <span class="card-title "><nobr>Energy Yesterday:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Yesterday}} kWh</nobr></span></span>
        </div>
        <div class="col s12">
          <span class="card-title "><nobr>Energy Today:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Today}} kWh</nobr></span></span>
        </div>
        <div class="col s12">
          <span class="card-title "><nobr>Energy Total:</nobr><span class="blue-text text-darken-2"><nobr> {{status.ENERGY.Total}} kWh</nobr></span></span>
        </div>
      </div>
    </div>
  </div>
</div>
  
</template>

<script>
import Service from './Service'

export default {
  name: 'ModuleInfo',
  props: [
      'customHeight'
  ],
  data(){
    return {
      status: {ENERGY:{Voltage:0,Power:0,Current:0,Factor:0,Yesterday:0,Today:0,Total:0}},
      state: false,
      timer: '',
      switch1: false,
    }
  },
  methods: {
    toggleSwitch(){
      this.setState(this.switch1);
    },
    setState(state){
      this.state = !this.state;
      this.switch1 = this.state;
      Service.setStatus(state);
    },
    update(data){
      this.status = data;
      this.$emit('set_loading', false);

      if ('POWER' in data) {
        if (data.POWER == 'ON'){
          this.switch1 = true;
          this.state = true;
        } else {
          this.switch1 = false;
          this.state = false;
        }
      }
    },
    fetchStatus(){
      Service.getStatus(this.update);
    }
  },
  mounted() {
    this.timer = setInterval(this.fetchStatus, 1000*3);
    this.fetchStatus();
  },
  beforeDestroy() {
    clearInterval(this.timer)
  }
}
</script>

<style scoped>
.switch{
  transform: scale(1.5);
  margin: 12% 0;
}

.strong{
  font-weight: bolder;
}

.power-button {
  padding: 2px;
  cursor: pointer;
  border-radius: 50%;
  user-select: none;
}

.power-button.green-text{
  color: rgb(21, 255, 0);
  text-shadow: 0 0 12px rgb(11, 255, 11);
}

.row{
  margin-bottom: 5px;
}

.card-content{
  padding-bottom: 0;
}


</style>
