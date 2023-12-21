export class StayDate {
    id: number = -1;
    startDate: Date = new Date();
    endDate: Date = new Date();

    toJSON() {
        return {
            startDate: this.formatDate(this.startDate),
            endDate: this.formatDate(this.endDate),
        };
    }
    
    private formatDate(date: Date): string {
        const day = String(date.getDate()).padStart(2, '0');
        const month = String(date.getMonth() + 1).padStart(2, '0');
        const year = date.getFullYear();
        return `${day}-${month}-${year}`;
    }
}