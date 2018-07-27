<template>
<div>

    <ul class="collection">
        <li v-for="(alert, index) in alerts" :key="index" class="collection-item">
            <div style="margin-right:20px;">{{alert.email}}</div><div>{{alert.level}} Bq/m³</div><div class="spacer"></div><button class="btn-small" @click="del(index)">Delete</button>
        </li>
    </ul>
    <div class="row">
        <div class="input-field col s6">
            <input id="email" type="email" v-model="newAlert.email">
            <label for="email">Email</label>
            <div v-show="error != ''" class="red-text">{{error}}</div>
        </div>
        <div class="input-field col s6">
            <input id="level" type="text" value="300" v-model="newAlert.level">
            <label for="level">Level of alert (Bq/m³)</label>
        </div>
        <button class="btn-large" @click="add()">Add</button>
    </div>
</div>
</template>

<script>
import Service from './Service'

export default {
    name: 'Alerts',
    data(){
        return {
            alerts: [{}],
            newAlert: {email: '', level:300},
            error: "",
        };
    },
    methods:{
        del(index){
            Service.delAlert(this.alerts[index].email);
            this.alerts.pop(index);
        },
        add(){
            if (true){//this.validEmail(this.newAlert.email)){
                this.alerts.push(this.newAlert);
                Service.addAlert(this.newAlert);
                this.error = "";
                this.newAlert =  {email: '', level:300};
            }
            else
                this.error = "The email is not valid";
        },
         validEmail: function (email) {
            var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
            return re.test(email);
        },
        update(alerts){
            this.alerts = alerts;
            this.$emit('set_loading', false);
        }
    },
    mounted() {
        Service.getAlerts(this.update);
    }
}
</script>

<style scoped>
.collection-item{
    display:flex;
}
.spacer{
  flex-grow: 1;
}
</style>


